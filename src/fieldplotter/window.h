#ifndef WINDOW_H_
#define WINDOW_H_

#include "graphics/glcontext.h"
#include <GLFW/glfw3.h>

#include "event/windowevent.h"

#include <string>
#include <algorithm>

struct GLVersion;
namespace fieldplotter {
    class Window {
        public:
            //TODO typedef
            // static const int CORE_PROFILE = GLFW_CORE_PROFILE;
            enum GLProfile {
                CORE_PROFILE=GLFW_OPENGL_CORE_PROFILE
            };
            struct WindowOptions {
                //TODO typedef
                std::pair<int, int> openGLVersion;
                GLProfile openGLProfile;
                std::string title;
                WindowOptions() {
                    openGLVersion = {4,5};
                    openGLProfile = CORE_PROFILE;
                    title = "Field Plotter";
                }
            };
            Window(WindowOptions const& options, int width, int height);
            Window(int width, int height) : Window(WindowOptions(), width, height) {}
            Window() : Window(800,600) {}
            ~Window();
            void show();
            void hide();
            void update();
            void close();
            void setEventCallback(EventCallback callback) { m_onEvent = callback; }
            void onEvent(Event const& event) { m_onEvent(event); }
            int getWidth() const;
            int getHeight() const;
            bool isClosed() const;
            OpenGLContext getContext() const;
        private:
            EventCallback m_onEvent;
            GLFWwindow* m_handle;
            int m_width;
            int m_height;
            bool m_closed; //TODO will be set by the windowshouldclose callback
            std::string m_title;
    };
}
#endif // WINDOW_H_
