#ifndef __CONTEXT_H_
#define __CONTEXT_H_
#include "vendor/graphics/api.h"
#include "frame.h"
#include <thread>

/*
** A context wrapper for a single rendering instance.
** A context should choose the rendering API (OpenGL, Vulkan, ...), as well as the framebuffer and the dimensions of the screen.
** It should contain information about the thread it is running on to disallow calls from other threads
*/
namespace rendering {
    //graphics dimensions (2d,3d) should not be part of the context because they
    //represent a mode that one can switch between in the graph high-level object
    template <enum RenderingAPI API>
    class Context {
        public:
            Context();
            ~Context();
            bool isValid() const;
        private:
            rendering::Frame<API> m_frame;
            std::thread m_thisthread;
            bool m_valid;
    };
}



#endif // __CONTEXT_H_
