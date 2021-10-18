#include "core.h"
#include "renderer.h"

using namespace fieldplotter;

Renderer::Renderer() {
    glClearColor(0.0f,0.0f,1.0f,0.5f);
}

Renderer::~Renderer() {

}

void Renderer::clear() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
