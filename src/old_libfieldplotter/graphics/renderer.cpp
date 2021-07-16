#include "renderer.h"

#include "../components/plottable.h"

#include <fieldplotter_pch.h>


Renderer::Renderer() {

}
void Renderer::initGraphics() {
    glewExperimental = GL_TRUE;
	GLenum glewinitialized = glewInit();
	if (glewinitialized != GLEW_OK) {
		std::cout << "GLEW FAILED TO INITIALIZE!\n";
	}
    
    glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

    glClearColor(0.0f, 0.1f, 0.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
}
void Renderer::render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
	glBindVertexArray(m_vao);

	m_scene->update();
	for (auto& element : m_plottables) {
		element->draw();
	}	
}
void Renderer::addObject(Plottable* plottable) {
    m_plottables.push_back(plottable);
}
void Renderer::removeObject(Plottable* plottable) {
    for (int i = 0; i < m_plottables.size(); i++) {
        if (m_plottables[i] == plottable) {
            m_plottables.erase(m_plottables.begin()+i);
            return;
        }
    }
}
void Renderer::setScene(Scene* scene) {
	m_scene = scene;
}
void Renderer::resizeScreen(int w, int h) {
    m_width=w;
    m_height=h;
	glViewport(0,0,w,h);
	m_scene->getUniforms().resizeProjection(w,h);
	m_scene->update();
}