#ifndef RENDERER_H_
#define RENDERER_H_

#include <GL/glew.h>
#include <vector>

#include "vao.h"

namespace fieldplotter{

    //straight up a memory allocator in here
    class Renderer {
        public:
            Renderer();
            ~Renderer();
            //add object
            //remove object
            void render();
        private:
            // std::vector<Drawable> objects;
            //Camera

        };
}

#endif // RENDERER_H_
