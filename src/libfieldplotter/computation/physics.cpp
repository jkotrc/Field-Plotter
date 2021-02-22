#include "physics.h"


#include "../components/chargesystem.h"
#include "../components/fieldlines.h"

#include <fieldplotter_pch.h>

using namespace std;

namespace {
    bool isOutOfBounds(Point const& point, const float range) {
        return (point.mag() >= range);
    }
    Point electrical_force_at(Point r, std::vector<PointCharge>& charges) {
        Point forceVector = Point(0.0f, 0.0f, 0.0f);
        for (int i = 0; i < charges.size(); i++) {
            const float charge_q = charges[i].charge;
            Point pos_difference = r - charges[i].p;
            const float magcubed = pos_difference.mag() * pos_difference.magsq();
            forceVector += (charge_q / magcubed) * pos_difference;
        }
        forceVector *= factor;
        return forceVector;
    }
}


void compute_field_lines(FieldLines::Configuration const& configuration, std::vector<PointCharge> const& charges, ReaderWriterQueue<Point>* vertex_queue, ReaderWriterQueue<int>* index_queue) {
//void compute_field_lines(ChargeSystem* system, FieldLines* p_lines, ReaderWriterQueue<Point>* vertex_queue, ReaderWriterQueue<int>* index_queue) {

    const float line_density = configuration.line_density;
    const float radius = 0.1f;//TODO: SET THIS!!!
    const float delta_theta = 2 * pi / (line_density);
    const float delta_phi = pi / (line_density);
    const float range = configuration.range;
    const float ds = configuration.ds;
    const float ds_visible = configuration.visible_ds;
    
    //std::vector<Point>& vertices = p_lines->getVertices();
    //std::vector<int>& p_lines_index = p_lines->getLinesIndex();

    std::vector<Point> sources;
    std::vector<Point> sinks;
    for (int i = 0; i < charges.size(); i++) {
        if (charges[i].charge > 0.0f) {
            sources.push_back(charges[i].p);
        }
        else {
            sinks.push_back(charges[i].p);
        }
    }

    int offset = 0;
    for (const Point& source : sources) {
        for (float theta = 0.0f; theta <= 2 * pi; theta += delta_theta) {
            for (float phi = 0.0f; phi <= pi; phi += delta_phi) {
                Point origin = Point
                (
                    (radius)*sinf(phi) * cosf(theta) + source.x,
                    (radius)*sinf(phi) * sinf(theta) + source.y, //OpenGL's y and z are switched!
                    (radius)*cosf(phi) + source.z
                    );

                vertex_queue->enqueue(origin);
                index_queue->enqueue(offset);
                //lines_index.push_back(offset);
                //vertices.push_back(origin);
                offset++;

                float cumulative_dF = 0.0f;
                while (true) {
                    Point dF1 = electrical_force_at(origin, charges) * ds;
                    Point dF2 = electrical_force_at(origin + dF1 * (ds / 2), charges) * ds;
                    Point dF3 = electrical_force_at(origin + dF2 * (ds / 2), charges) * ds;
                    Point dF4 = electrical_force_at(origin + dF3 * (ds), charges) * ds;
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
                        vertex_queue->enqueue(origin);
                        //vertices.push_back(origin);
                        offset++;
                        cumulative_dF = 0.0f;
                        break;
                    }
                    if (cumulative_dF >= ds_visible) {
                        //assert(origin.mag() > 0.01f);
                        vertex_queue->enqueue(origin);
                        //vertices.push_back(origin);
                        offset++;
                        cumulative_dF = 0.0f;
                    }

                }
            }
        }
    }
    p_lines->finishComputation();
}
    
/*
void compute_electric_field(DynamicObject* p_vf, ChargeSystem& system) {
    VectorField* vf = (VectorField*)p_vf;
    PointCharge* charges = system->getCharges();
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
*/
