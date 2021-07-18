#include "fieldplotter.h"

#include <iostream>

using namespace fieldplotter;

FieldPlotter::FieldPlotter(int window_width, int window_height) {
    m_window = new Window(window_width, window_height, "Field Plotter");
    m_context = new OpenGLContext(FP_OPENGL_VERSION);
}

int FieldPlotter::begin() {
    // if (!glewIsSupported("GL_VERSION_4_6")) {
    //     std::cerr << "GL Version 4.6 not supported!\n";
    //     return 1;
    // }
    m_window->setOpenGLVersion(FP_OPENGL_VERSION);
    if (!m_window->create()) {
        std::cerr << "Window failed to create!\n";
        return 1;
    }
    if (!m_context->initialize()) {
        std::cerr << "GLEW failed to initialize!\n";
        return 1;
    }
    while (!m_window->shouldClose()) {
        //TODO add event dispatching here
        m_window->update();
    }
    return 0;
}
