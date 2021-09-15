#ifndef RENDERER_H_
#define RENDERER_H_

#include "glcontext.h"

namespace fieldplotter{
    class Renderer {
        public:
            Renderer(OpenGLContext const& context);
            ~Renderer();
            void render();
    };
}

#endif // RENDERER_H_
