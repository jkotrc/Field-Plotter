#include "computation.h"

#include "physicalobject.h"
#include "chargesystem.h"
#include "vectorfield.h"
#include "fieldlines.h"

#include <vector>
#include <thread>
#include <cmath>
#include <iostream>

using namespace std;

vector<thread> Computation::active_threads;

#define PERMITTIVITY 8.8541878128f
#define PI 3.141592653f
const float factor = 1/(4 * PI * PERMITTIVITY);

bool isOutOfBounds(Point point, float range) {
    return (point.mag() >= range);
}

void compute_field_lines(PhysicalObject* p_lines, ChargeSystem& system) {
    FieldLines* lines = (FieldLines*)p_lines;
    float line_density = lines->getLineDensity();
    const float radius = 0.1f;//TODO: SET THIS!!!
    const float delta_theta = 2 * PI / (line_density);
    const float delta_phi = PI / (line_density);
    const float range = lines->getRange();
    const float ds = lines->getLineStep();

    //TODO: RK4 needs a small step for accuracy but we don't need that many vertices as it makes no visible difference
    const float ds_visible = 0.05f;//TODO: SET THIS!!

    PointCharge* charges = system.getCharges();
    std::vector<Point>& vertices = lines->getVertices();
    std::vector<int>& lines_index = lines->getLinesIndex();
    std::vector<Point> sources;
    std::vector<Point> sinks;
    for (int i = 0; i < system.getN(); i++) {
        if (charges[i].charge > 0.0f) {
            sources.push_back(charges[i].p);
        }
        else {
            sinks.push_back(charges[i].p);
        }
    }

    int offset = 0;
    for (const Point& source : sources) {
        for (float theta = 0.0f; theta <= 2 * PI; theta += delta_theta) {
            for (float phi = 0.0f; phi <= PI; phi += delta_phi) {
                Point origin = Point
                (
                (radius)*sinf(phi) * cosf(theta) + source.x,
                    (radius)*sinf(phi) * sinf(theta) + source.y, //OpenGL's y and z are switched!
                    (radius)*cosf(phi) + source.z
                    );

                lines_index.push_back(offset);
                vertices.push_back(origin);
                offset++;

                float cumulative_dF = 0.0f;
                while (true) {
                    Point dF1 = electrical_force_at(origin, system) * ds;
                    Point dF2 = electrical_force_at(origin + dF1 * (ds / 2), system) * ds;
                    Point dF3 = electrical_force_at(origin + dF2 * (ds / 2), system) * ds;
                    Point dF4 = electrical_force_at(origin + dF3 * (ds), system) * ds;
                    Point dF = dF1 + 2 * dF2 + 2 * dF3 + dF4;
                    dF *= ds;
                    dF /= 6.0f;
                    origin += dF;
                    cumulative_dF += dF.mag();

                    bool lineEnded = false;
                    for (const Point& sink : sinks) {
                        if ((origin - sink).mag() <= radius)
                        {
                            lineEnded = true;
                            break;
                        }
                    }
                    if (isOutOfBounds(origin, range) || (dF.mag() < 1e-9f)) {
                        lineEnded = true;
                    };
                    if (lineEnded) {
                        vertices.push_back(origin);
                        offset++;
                        cumulative_dF = 0.0f;
                        break;
                    }

                    if (cumulative_dF >= ds_visible) {
                        vertices.push_back(origin);
                        offset++;
                        cumulative_dF = 0.0f;
                    }

                }
            }
        }
    }
    printf("aight;\n");
}
    

Point electrical_force_at(Point r,ChargeSystem& system) {
    PointCharge* charges = system.getCharges();
    Point forceVector=Point(0.0f,0.0f,0.0f);
        for (int i = 0; i < system.getN(); i++) {
            const float charge_q = charges[i].charge;
            Point pos_difference = r-charges[i].p;
            const float magcubed = pos_difference.mag()*pos_difference.magsq();
            forceVector += (charge_q/magcubed)*pos_difference;
        }
        forceVector*=factor;
    return forceVector;
}

void compute_electric_field(PhysicalObject* p_vf, ChargeSystem& system) {
    VectorField* vf = (VectorField*)p_vf;
    PointCharge* charges = system.getCharges();
    const int vectorfield_dimension = vf->getAmount();
    
    float lowerbound = 0.0f;
    float upperbound = 1.0f;
    for (int i = 0; i < vectorfield_dimension; i++) {
        Vector vec = vf->getVector(i);
        
        Point forceVector = electrical_force_at(*vec.pos,system);
        float mag=forceVector.mag();
        *vec.component = forceVector;
        if (mag > upperbound) {
            upperbound = mag;
        }
        if (mag < lowerbound) {
            lowerbound = mag;
        }
    }
    vf->setUpperBound(upperbound/30);
    vf->setLowerBound(lowerbound);
}

Computation::Computation(
    PhysicalObject* comp,
    ChargeSystem& charge_system,
    void (*func)(PhysicalObject* object, ChargeSystem& system))
    :completed(false), component(comp), compute_function(func), charge_system(charge_system) {

}

PhysicalObject* Computation::getComponent() { return component; }

bool Computation::isComplete() { return completed; }

void Computation::run() {
    int a = 0;
    component->setComputationalState(true);
    component->setComputed(true);
    compute_function(component, charge_system);
    component->setComputationalState(false);
    onFinalize();
    component->updateBuffers();
    for (thread& t : Computation::active_threads) {
        if (t.get_id() == this_thread::get_id()) {
            t.detach();
        }
    }
}

void Computation::spawnThread() {
    Computation::active_threads.push_back(thread(&Computation::run,this));
}