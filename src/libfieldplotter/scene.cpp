#include "scene.h"
#include "dynamicobject.h"

#include "Shaders.h"


using namespace glm;


/*
std140 specification:
layout (std140) uniform Block{
                     // base alignment  // aligned offset
    float value;     // 4               // 0 
    vec3 vector;     // 16              // 16  (offset must be multiple of 16 so 4->16)
    mat4 matrix;     // 16              // 32  (column 0)
                     // 16              // 48  (column 1)
                     // 16              // 64  (column 2)
                     // 16              // 80  (column 3)
    float values[3]; // 16              // 96  (values[0])
                     // 16              // 112 (values[1])
                     // 16              // 128 (values[2])
    bool boolean;    // 4               // 144
    int integer;     // 4               // 148
};
*/

#define MAT4_BASE_ALIGNMENT 16
#define VEC3_BASE_ALIGNMENT 16

Scene::Scene(int width, int height) 
:
m_projectionMatrix(glm::perspective(glm::radians(45.0f), (float)width/height, 0.1f, 100.0f)),
m_viewMatrix(rotate(mat4(1.0f), 1.0f, vec3(1.0, 0.0, 0.0))),
m_camera()
{
	initGraphics();
}

void Scene::initGraphics() {
	glewExperimental = GL_TRUE;
	GLenum glewinitialized = glewInit();

	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);

	glGenBuffers(1, &m_uniformbuffer);
	glBindBuffer(GL_UNIFORM_BUFFER, m_uniformbuffer);
	glBufferData(GL_UNIFORM_BUFFER, 2 * sizeof(mat4) + sizeof(vec3), NULL, GL_STATIC_DRAW);

	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(mat4), glm::value_ptr(m_projectionMatrix));
	glBufferSubData(GL_UNIFORM_BUFFER, sizeof(mat4), sizeof(mat4), glm::value_ptr(m_viewMatrix));
	glBufferSubData(GL_UNIFORM_BUFFER, 2 * sizeof(mat4), sizeof(vec3), glm::value_ptr(m_camera.getPos()));
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
	glBindBufferBase(GL_UNIFORM_BUFFER, 0, m_uniformbuffer);
}

void Scene::addPlottable(Plottable* component) {
	component->setParent(this);
	component->initGraphics();
	m_plottables.push_back(component);
}

void Scene::removePlottable(Plottable* component) {
	//TODO: implement
}

void Scene::resizeViewport(int w, int h) {
	//TODO: Make this orthographic when the user wants a 2D-like view
	m_projectionMatrix = glm::perspective(glm::radians(45.0f), (float)w / h, 0.1f, 100.0f);
	glBindBuffer(GL_UNIFORM_BUFFER, m_uniformbuffer);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(mat4), glm::value_ptr(m_projectionMatrix));
	glBindBuffer(GL_UNIFORM_BUFFER,0);
	glViewport(0, 0, w, h);
}

void Scene::render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBindVertexArray(m_vao);
	m_viewMatrix = m_camera.getViewMatrix();
	glBindBuffer(GL_UNIFORM_BUFFER, m_uniformbuffer);
	glBufferSubData(GL_UNIFORM_BUFFER, sizeof(mat4), sizeof(mat4), glm::value_ptr(m_viewMatrix));
	glBufferSubData(GL_UNIFORM_BUFFER, sizeof(mat4)*2,sizeof(vec3),glm::value_ptr(m_camera.getPos()));
	glBindBuffer(GL_UNIFORM_BUFFER,0);
	for (auto& element : m_plottables) {
		element->draw();
	}
}
Camera& Scene::getCamera() {
	return m_camera;
}
GLuint Scene::getSceneMatrices() {
	return m_uniformbuffer;
}