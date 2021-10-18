#ifndef RENDERER_H_
#define RENDERER_H_

#define GLEW_STATIC
#include <GL/glew.h>

namespace fieldplotter{
    class Renderer {
        public:
            Renderer();
            ~Renderer();
            void clear();
    };
}

#endif // RENDERER_H_
