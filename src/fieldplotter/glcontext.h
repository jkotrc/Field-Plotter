#ifndef GLCONTEXT_H_
#define GLCONTEXT_H_
#include <GL/glew.h>

namespace fieldplotter {
    struct GLVersion {
        int major;
        int minor;
        GLVersion(int major, int minor) : major(major), minor(minor){}
    };

    class OpenGLContext {
        public:
            OpenGLContext(GLVersion version);
            bool initialize();
            bool initialized();
            GLVersion getVersion() const;
        private:
            bool m_initialized;
            GLVersion m_version;
    };
}


#endif // GLCONTEXT_H_
