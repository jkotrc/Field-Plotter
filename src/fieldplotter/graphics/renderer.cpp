#include "core.h"
#include "renderer.h"

using namespace fieldplotter;

Renderer::Renderer(OpenGLContext const& context) {
    if (!context.isValid()) {
        DEBUG_ERR("Renderer not made due to invalid context")
    }
    glClearColor(0.0f,0.0f,1.0f,0.5f);
}

Renderer::~Renderer() {

}

void Renderer::render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
