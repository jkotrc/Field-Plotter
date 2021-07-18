#include "glcontext.h"

#include <boost/log/trivial.hpp>

using namespace fieldplotter;

OpenGLContext::OpenGLContext(GLVersion version) : m_version(version){}

bool OpenGLContext::initialize() {
    glewExperimental=true;
    GLenum err = glewInit();
    m_initialized = (err == GLEW_OK);
    if (!m_initialized) {
        BOOST_LOG_TRIVIAL(error) << glewGetErrorString(err);
    }
    return m_initialized;
}

bool OpenGLContext::initialized() {
    return m_initialized;
}

GLVersion OpenGLContext::getVersion() const {
    return m_version;
}
