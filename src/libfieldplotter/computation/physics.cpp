#include <fieldplotter/fieldplotter.h>
#define PERMITTIVITY 8.8541878128f
#define PI 3.141592653f


//TODO: This NEEEDS to be changed!
using namespace glm;
void compute_electric_field(VectorField& vf, ChargeSystem& system/*PhysicsConfiguration configuration*/) {
    PointCharge* charges = system.getCharges();

    const int vectorfield_dimension = vf.getAmount();
    const float permDivisor = 4 * PI * PERMITTIVITY;

    float lowerbound = 0.0f;
    float upperbound = 1.0f;

    for (int i = 0; i < vectorfield_dimension; i++) {

        Vector vec = vf.getVector(i);
        float* positions = vec.pos;
        float* components = vec.component;
        vec3 posvec = vec3(positions[0], positions[1], positions[2]);
        vec3 compvec = vec3(components[0], components[1], components[2]);
        float mag = 0.0f;
        for (int i = 0; i < 3; ++i) {
            float result = 0.0f;
            for (int j = 0; j < system.getN(); j++) {
                const vec3 chargepos = vec3(charges[j].p.x, charges[j].p.y, charges[j].p.z);
                const float magcubed = glm::length(posvec - chargepos)* glm::length(posvec - chargepos)* glm::length(posvec - chargepos);
                result += charges[j].charge * (posvec[i] - chargepos[i]) / magcubed;
            }

            result /= permDivisor;
            components[i] = result;
            mag += components[i] * components[i];
        }
        mag = sqrtf32(mag);
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