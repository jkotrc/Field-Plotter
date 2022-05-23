#ifndef ELECTROSTATICS_H_
#define ELECTROSTATICS_H_

#include <glm/glm.hpp>
#include <vector>

//permittivity = 8.854*10^-12

namespace fieldplotter {

    struct Charge {
        float q;
        glm::vec2 pos;
        float size;
    };

    glm::vec2 forceAt(glm::vec2 const& point, std::vector<Charge> const& charges);
}

#endif // ELECTROSTATICS_H_
