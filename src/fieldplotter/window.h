#ifndef WINDOW_H_
#define WINDOW_H_

#include <graphics/glgraphics.h>
#include <GLFW/glfw3.h>

#include "event/windowevent.h"

#include <string>
#include <algorithm>
#include <memory>
#include <set>

struct GLVersion;
namespace fieldplotter {

using vec2d = glm::vec<2, double>;

    class Window {
        public:
            struct WindowOptions {
                std::string title;
                unsigned int width, height;
                WindowOptions() {
                    width = 800;
                    height = 800;
                    title = "Field Plotter";
                }
            };

            Window();
            ~Window();

            void show();
            void hide();
            void update();
            void close();
            void draw();

            void setEventCallback(EventCallback callback) { event_callback = callback; }
            void onEvent(Event const& event);

            int getWidth() const;
            int getHeight() const;
            bool isClosed() const;
            Graphics& getGraphics() const { return *graphics;}
            glm::vec<2, double> getMousePosition() const;
            glm::vec<2, double> getMouseVelocity() const;
            bool leftMbtnDown() const {return mousebuttons.find(GLFW_MOUSE_BUTTON_LEFT) != mousebuttons.end();}
            bool rightMbtnDown() const {return mousebuttons.find(GLFW_MOUSE_BUTTON_RIGHT) != mousebuttons.end();}
        private:
            void errorCallback(int code, const char* desc);
            EventCallback event_callback;
            GLFWwindow* handle;
            std::unique_ptr<OpenGLGraphics> graphics;
            int width;
            int height;
            bool closed; //TODO will be set by the windowshouldclose callback
            std::string title;
            std::set<unsigned int> mousebuttons;
            vec2d mousepos = {0, 0};
            vec2d mousevel = {0, 0};
    };
}
#endif // WINDOW_H_
