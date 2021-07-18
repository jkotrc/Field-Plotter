#ifndef FIELDPLOTTER_H_
#define FIELDPLOTTER_H_

#include "glcontext.h"
#include "window.h"
//#include "inputdispatcher.h"

/*
** TODO implement runtime checks for OpenGL support
*/

static const fieldplotter::GLVersion FP_OPENGL_VERSION = {4,6};

namespace fieldplotter {
    class FieldPlotter {
        public:
            FieldPlotter(int window_width, int window_height);
            int begin();
        private:
            OpenGLContext* m_context;
            Window* m_window;
            //InputDispatcher* m_dispatcher;
    };

}
#endif // FIELDPLOTTER_H_
