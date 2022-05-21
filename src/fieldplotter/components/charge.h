#ifndef CHARGE_H_
#define CHARGE_H_

#include <glm/glm.hpp>

namespace fieldplotter {

    struct Charge {
        float q;
        glm::vec2 pos;
        float size;
    };
}

#endif // CHARGE_H_
