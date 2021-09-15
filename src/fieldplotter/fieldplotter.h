#ifndef FIELDPLOTTER_H_
#define FIELDPLOTTER_H_

#include "glcontext.h"
#include "window.h"
#include "event.h"
#include "renderer.h"

namespace fieldplotter {
    class FieldPlotter {
        public:
            FieldPlotter();
            ~FieldPlotter();
            void run();
            void onEvent(Event const& e);
            void close();
        private:
            bool m_running;
            bool m_minimized;
    };

}
#endif // FIELDPLOTTER_H_
