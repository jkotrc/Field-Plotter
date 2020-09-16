#include "physics.h"

#define PERMITTIVITY 8.8541878128f
#define PI 3.141592653f

/*
typedef struct {
    PointCharge* charges;
    int n_charges;
} PhysicsConfiguration;
*/

//PointCharge {Point p, float charge}
//Point{float x,y,z}

//TODO: make this run a CUDA kernel if there is a valid device on the host computer


//inline float magcubed()


//TODO: This NEEEDS to be changed!
//using namespace glm;

// void compute_electric_field(VectorField* vf, PhysicsConfiguration configuration) {

//     const int vectorfield_dimension = vf->getAmount();
//     const float permDivisor = 4 * PI * PERMITTIVITY;

//     float lowerbound = 0.0f;
//     float upperbound = 1.0f;

//     for (int i = 0; i < vectorfield_dimension; i++) {
//         Vector vec = vf->getVector(i);
//         float* positions = vec.pos;
//         float* components = vec.component;
//         vec3 posvec = vec3(positions[0], positions[1], positions[2]);
//         vec3 compvec = vec3(components[0], components[1], components[2]);
//         //printf("POSITION: (%f,%f,%f)\n",*positions,*(positions+1),*(positions+2));
//         const float* end = (components + 3);

        

//         float mag = 0.0f;

//         //float chargeloc[3] = {};
//         for (int i = 0; i < 3; ++i) {


//             float result = 0.0f;
//             for (int j = 0; j < configuration.n_charges; j++) {
//                 const PointCharge charge = configuration.charges[j];
//                 const vec3 chargepos = vec3(charge.p.x, charge.p.y, charge.p.z);
//                 const float magcubed = glm::length(posvec - chargepos)* glm::length(posvec - chargepos)* glm::length(posvec - chargepos);
//                 result += charge.charge * (posvec[i] - chargepos[i]) / magcubed;
//             }

//             result /= permDivisor;
//             components[i] = result;
//             mag += components[i] * components[i];
//         }
//         mag = (float)sqrt(mag);
//         if (mag > upperbound) {
//             upperbound = mag;
//         }
//         if (mag < lowerbound) {
//             lowerbound = mag;
//         }

//     }
//     vf->setUpperBound(upperbound/30);
//     vf->setLowerBound(lowerbound);
// }