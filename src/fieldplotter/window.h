#ifndef WINDOW_H_
#define WINDOW_H_

#include <GLFW/glfw3.h>

#include <string>

struct GLVersion;
namespace fieldplotter {
    class Window {
        public:
            Window(int width, int height, std::string title);
            ~Window();
            bool create();
            void show();
            void hide();
            void setOpenGLVersion(GLVersion version);
            bool shouldClose();
            bool exists();
            int getWidth();
            int getHeight();
            void update();
        private:
            GLFWwindow* m_handle;
            std::string m_title;
            bool m_exists;
            bool m_hidden;
            int m_width;
            int m_height;
    };
}
#endif // WINDOW_H_
