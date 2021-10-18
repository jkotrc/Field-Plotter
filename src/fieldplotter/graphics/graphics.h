#ifndef GRAPHICS_H_
#define GRAPHICS_H_

#include "renderer.h"
#include <array>
#include <glm/glm.hpp>

namespace fieldplotter {
    class Graphics {
        public:
            Graphics();
            void clear();
            void drawLines(glm::vec3* points, size_t amount);
    private:
            Renderer m_renderer;
    };
}

#endif // GRAPHICS_H_
