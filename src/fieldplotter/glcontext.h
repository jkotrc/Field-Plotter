#ifndef GLCONTEXT_H_
#define GLCONTEXT_H_
#define GLEW_STATIC
#include <GL/glew.h>
#include <functional>
#include <algorithm>
#include <string>
/*
** For the future, maybe do a dependency injection into a
*rendering-platform-agnostic Context class instead
*/
namespace fieldplotter {
class OpenGLContext {
    public:
        typedef void (*ErrorCallback)(GLenum,GLenum,GLuint,GLenum,GLsizei,const GLchar*,const void*);
        OpenGLContext() { m_valid = (glewInit() == GLEW_OK); }
        bool isValid() const { return m_valid; }
        void setErrorCallback(ErrorCallback callback) {
            m_callback=callback;
            glDebugMessageCallback(m_callback, nullptr);
        }
        std::pair<int,int> getVersion() const {
            std::string versionString((const char*)glGetString(GL_VERSION));
            const int dotposition = versionString.find('.');
            return {std::atoi(versionString.substr(0,dotposition).c_str()), std::atoi(versionString.substr(dotposition+1,versionString.length()).c_str())};
        }
    private:
        ErrorCallback m_callback;
        bool m_valid;
};
} // namespace fieldplotter

#endif // GLCONTEXT_H_
