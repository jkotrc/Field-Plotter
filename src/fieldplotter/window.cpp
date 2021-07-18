#include "glcontext.h"
#include "window.h"

#include <boost/log/trivial.hpp>

using namespace fieldplotter;

namespace {
    void error_callback(int error, const char* description) {
        BOOST_LOG_TRIVIAL(error) << "error code " << error << "\ndescription:" << description;
    }
}

Window::Window(int width, int height, std::string title) : m_width(width), m_height(height), m_hidden(false), m_exists(false), m_title(title) {}

Window::~Window() {
    glfwDestroyWindow(m_handle);
    glfwTerminate();
}

bool Window::create() {
    if (!glfwInit()) {
        return false;
    }
    m_handle = glfwCreateWindow(m_width, m_height, m_title.c_str(), NULL, NULL);
    if (m_handle == NULL) {
        return false;
    }
    if (m_hidden) hide();
    glfwMakeContextCurrent(m_handle);
    return true;
}

void Window::show() {
    m_hidden=true;
    glfwShowWindow(m_handle);
}

void Window::hide() {
    m_hidden=false;
    glfwHideWindow(m_handle);
}

void Window::setOpenGLVersion(GLVersion version) {
    glfwWindowHint(GL_MINOR_VERSION, version.minor);
    glfwWindowHint(GL_MAJOR_VERSION, version.major);
}

bool Window::shouldClose() {
    return glfwWindowShouldClose(m_handle);
}

bool Window::exists() {
    return m_exists;
}

void Window::update() {
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(m_handle);
    glfwPollEvents();
}

int Window::getWidth() {
    return m_width;
}

int Window::getHeight() {
    return m_height;
}
