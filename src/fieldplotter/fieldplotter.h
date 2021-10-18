#ifndef FIELDPLOTTER_H_
#define FIELDPLOTTER_H_

#include <memory>
#include <chrono>
#include <string>

#include "graphics/glcontext.h"
#include "window.h"

#include "event/event.h"

using namespace std::chrono_literals;

/*
** This is a prototype appplication instance. It does not do much at the
** moment but each integration stage should come with an expansion of its interface
*/
namespace fieldplotter {
    class FieldPlotter {
        public:
            FieldPlotter(); //Don't instantiate more than once! multiple contexts still unsupported

            ~FieldPlotter();

            void update();

            void run(int seconds);

            void run();

            void onEvent(Event const& e);

            void close();

            void renderToPicture(std::string path);

            std::weak_ptr<Graphics> getGraphics() const;

        private:
            std::unique_ptr<Window> m_window;
            std::unique_ptr<OpenGLContext> m_context;
            bool m_running;
            bool m_minimized;
    };

}
#endif // FIELDPLOTTER_H_
