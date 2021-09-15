#ifndef FIELDPLOTTER_H_
#define FIELDPLOTTER_H_

#include "glcontext.h"
#include "window.h"
#include "renderer.h"
//#include "inputdispatcher.h"

/*
** TODO implement runtime checks for OpenGL support
*/

namespace fieldplotter {
    class FieldPlotter {
        public:
            FieldPlotter();
            ~FieldPlotter();
            void run();
            //onEvent(Event& e)
            void close();
        private:
            bool m_running;
            bool m_minimized;

    };

}
#endif // FIELDPLOTTER_H_
