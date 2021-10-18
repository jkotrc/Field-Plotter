#ifndef GLCONTEXT_H_
#define GLCONTEXT_H_

#define GLEW_STATIC
#include <GL/glew.h>

#include <functional>
#include <algorithm>
#include <string>
#include <memory>

#include "event/event.h"
#include "window.h"

#include "graphics.h"

namespace fieldplotter {

//This might be better structured as an object made from a factory class..
class OpenGLContext {
    public:
        typedef void (*ErrorCallback)(GLenum,GLenum,GLuint,GLenum,GLsizei,const GLchar*,const void*);

        OpenGLContext(Window const& contextprovider) {
            if (glewInit() != GLEW_OK) {
                DEBUG_ERR("glewInit failed!")
                throw "OpenGLContext failed to create";
            }
            graphicsInstance = std::shared_ptr<Graphics>(new Graphics());
        }

        // OpenGLContext() { m_valid = (glewInit() == GLEW_OK); }
        void setErrorCallback(ErrorCallback callback) {
            m_callback=callback;
            glDebugMessageCallback(m_callback, nullptr);
        }

        std::pair<int,int> getVersion() const {
            std::string versionString((const char*)glGetString(GL_VERSION));
            const int dotposition = versionString.find('.');
            return {std::atoi(versionString.substr(0,dotposition).c_str()), std::atoi(versionString.substr(dotposition+1,versionString.length()).c_str())};
        }

        std::weak_ptr<Graphics> getGraphics() const {
            return std::weak_ptr<Graphics>(graphicsInstance);
        }

    private:
        std::shared_ptr<Graphics> graphicsInstance;
        ErrorCallback m_callback;
};
} // namespace fieldplotter

#endif // GLCONTEXT_H_
