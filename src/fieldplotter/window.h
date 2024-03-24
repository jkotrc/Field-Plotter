#ifndef WINDOW_H_
#define WINDOW_H_

#include <graphics/glgraphics.h>
#include <GLFW/glfw3.h>

#include "event/windowevent.h"

#include <string>
#include <algorithm>
#include <memory>

struct GLVersion;
namespace fieldplotter {
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
            void onEvent(Event const& event) { event_callback(event); }

            int getWidth() const;
            int getHeight() const;
            bool isClosed() const;
            Graphics& getGraphics() const { return *graphics;}
        private:
            void errorCallback(int code, const char* desc);
            EventCallback event_callback;
            GLFWwindow* handle;
            std::unique_ptr<OpenGLGraphics> graphics;
            int width;
            int height;
            bool closed; //TODO will be set by the windowshouldclose callback
            std::string title;
    };
}
#endif // WINDOW_H_
