#include "core.h"
#include "glcontext.h"
#include "window.h"

#include <boost/log/trivial.hpp>

using namespace fieldplotter;

Window::Window(WindowOptions const& options, int width, int height)
    : m_width(width), m_height(height), m_title(options.title) {
    if (glfwInit() != GLFW_TRUE) {
        DEBUG_ERR("Failed to create GLFW");
        throw "Failed to create GLFW Instance";
    }
    m_handle = glfwCreateWindow(width, height, options.title.c_str(), NULL, NULL);
    if (m_handle == nullptr) {
        DEBUG_ERR("Failed to create window!");
        throw "Failed to create window!";
    }
    DEBUG_MSG("Setting version to:")
    DEBUG_MSG(options.openGLVersion.first)
    DEBUG_MSG(options.openGLVersion.second)
    glfwSetWindowAttrib(m_handle, GLFW_CONTEXT_VERSION_MINOR, options.openGLVersion.first);
    glfwSetWindowAttrib(m_handle, GLFW_CONTEXT_VERSION_MAJOR, options.openGLVersion.second);
    glfwSetWindowAttrib(m_handle, GLFW_OPENGL_PROFILE, options.openGLProfile);
#ifdef debug
    glfwSetWindowAttrib(m_handle, GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
#endif
}

Window::~Window() {
    this->close();
    glfwDestroyWindow(m_handle);
    glfwTerminate();
}

void Window::show() {
    //TODO onShowEvent
    glfwShowWindow(m_handle);
}

void Window::hide() {
    //TODO onHideEvent
    glfwHideWindow(m_handle);
}

void Window::update() {
    glfwSwapBuffers(m_handle);
    glfwPollEvents();
}

void Window::close() {
    glfwSetWindowShouldClose(m_handle, GLFW_TRUE);
}

int Window::getWidth() const {
    return m_width;
}

int Window::getHeight() const {
    return m_height;
}

bool Window::isClosed() const {
    return m_closed;
}

OpenGLContext Window::getContext() const {
    glfwMakeContextCurrent(m_handle);
    return {};
}
