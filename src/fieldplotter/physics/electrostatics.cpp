#include "electrostatics.h"

using namespace fieldplotter;
using namespace glm;

float magnitude2(vec2 x) {
    float mag = glm::length(x);
    return mag * mag;
}

vec2 fieldplotter::forceAt(vec2 const& point, std::vector<Charge> const& charges) {
    vec2 force = {0.0f,0.0f};
    for (const auto charge : charges) {
        vec2 direction = point - charge.pos;
        float mag3 = magnitude2(direction) * glm::length(direction);
        force += (charge.q / mag3) * direction;
    }
    return force;
}
