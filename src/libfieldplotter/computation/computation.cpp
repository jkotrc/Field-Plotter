#include <fieldplotter/computation.h>
#include <fieldplotter/fieldplotter.h>
#define PERMITTIVITY 8.8541878128f
#define PI 3.141592653f
const float factor = 1/(4 * PI * PERMITTIVITY);

bool isOutOfBounds(Point point, float range) {
    return (fabsf(point.x) >= range || fabsf(point.y) >= range || fabsf(point.z) >= range);
}

//This will break if it is called more than once
//test this!
void compute_field_lines(FieldLines& lines, ChargeSystem& system){
    float line_density = lines.getLineDensity();    
    const float radius = 0.1f;
    const float delta_theta = 2 * PI / (4.0f*line_density);
	const float delta_phi = PI / (4.0f*line_density);
    const float range = lines.getRange();
    const float ds = lines.getLineStep();

    PointCharge* charges = system.getCharges();
    std::vector<Point> vertices = lines.getVertices();
    std::vector<Point> sources;
    std::vector<Point> sinks;
    for (int i = 0; i < system.getN(); i++) {
        if (charges[i].charge > 0.0f) {
            sources.push_back(charges[i].p);
        } else {
            sinks.push_back(charges[i].p);
        }
    }

    for (const Point& source : sources) {
        for (float theta=0.0f; theta <= 2*PI; theta+=delta_theta) {
            for (float phi=0.0f; phi <= PI; phi+=delta_phi) {
                Point origin = Point 
                (
                    radius*sinf(phi)*cosf(theta),
                    radius*sinf(phi)*sinf(theta), //OpenGL's y and z are switched!
                    radius*cosf(phi)
                );
                vertices.push_back(origin);
                while(true) {
                    for(const Point& sink : sinks) {
                        if((origin-sink).mag()<=0.1f)break;
                    }
                    if(isOutOfBounds(origin,range)) break;
                    Point dF1 = electrical_force_at(origin,system)*ds;
                    Point dF2 = electrical_force_at(origin+Point(ds*dF1.x/2,ds*dF1.y/2,ds*dF1.z/2),system)*ds;
                    Point dF3 = electrical_force_at(origin+Point(ds*dF2.x/2,ds*dF2.y/2,ds*dF2.z/2),system)*ds;
                    Point dF4 = electrical_force_at(origin+Point(ds*dF3.x,ds*dF3.y,ds*dF3.z),system)*ds;
                    origin = origin + (dF1+dF2*2+dF3*2+dF4)/6;
                    vertices.push_back(origin);
                }
                vertices.push_back(vertices[vertices.size()-1]);//terminate the line when it ends
            }
        }
    }
}
    

Point electrical_force_at(Point r,ChargeSystem& system) {
    PointCharge* charges = system.getCharges();
    Point forceVector=Point(0.0f,0.0f,0.0f);
        for (int i = 0; i < system.getN(); i++) {
            const float charge_q = charges[i].charge;
            Point pos_difference = r-charges[i].p;
            const float magcubed = pos_difference.mag()*pos_difference.magsq();
            forceVector = forceVector + pos_difference*(charge_q/magcubed);
        }
        forceVector=forceVector*factor;
    return forceVector;
}

void compute_electric_field(VectorField& vf, ChargeSystem& system) {
    PointCharge* charges = system.getCharges();
    const int vectorfield_dimension = vf.getAmount();
    
    float lowerbound = 0.0f;
    float upperbound = 1.0f;
    for (int i = 0; i < vectorfield_dimension; i++) {
        Vector vec = vf.getVector(i);
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
    vf.setUpperBound(upperbound/30);
    vf.setLowerBound(lowerbound);
}