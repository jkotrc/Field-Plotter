#include <fieldplotter/commonheaders.h>
#include <fieldplotter/scene.h>
#include <fieldplotter/plottable.h>

#include "Shaders.h"
#include <stdio.h>


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
:height(height),
width(width),
projectionMat(glm::perspective(glm::radians(45.0f), (float)width/height, 0.1f, 100.0f)),
viewMat(rotate(mat4(1.0f), 1.0f, vec3(1.0, 0.0, 0.0))),
camera(new Camera())
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glClearColor(0.1, 0.1, 0.1, 1);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
	
	glGenBuffers(1, &sceneMatrices);
	glBindBuffer(GL_UNIFORM_BUFFER, sceneMatrices);
	glBufferData(GL_UNIFORM_BUFFER, 2*sizeof(mat4)+sizeof(vec3),NULL,GL_STATIC_DRAW);
	
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(mat4), glm::value_ptr(projectionMat));
	glBufferSubData(GL_UNIFORM_BUFFER, sizeof(mat4), sizeof(mat4), glm::value_ptr(viewMat));
	glBufferSubData(GL_UNIFORM_BUFFER, 2*sizeof(mat4), sizeof(vec3),glm::value_ptr(camera->getPos()));
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
	glBindBufferBase(GL_UNIFORM_BUFFER,0,sceneMatrices);
}

void Scene::addPlottable(Plottable* plottable) {
	plottable->setParent(this);
	plottable->initGraphics();
	plottables.push_back(plottable);
}

void Scene::resizeViewport(int w, int h) {
	width=w;
	height=h;
	//TODO: Make this orthographic when the user wants a 2D-like view
	projectionMat = glm::perspective(glm::radians(45.0f), (float)w / h, 0.1f, 100.0f);
	glBindBuffer(GL_UNIFORM_BUFFER, sceneMatrices);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(mat4), glm::value_ptr(projectionMat));
	glBindBuffer(GL_UNIFORM_BUFFER,0);
	glViewport(0, 0, width, height);
}

void Scene::render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBindVertexArray(vao);
	viewMat = camera->getViewMatrix();
	glBindBuffer(GL_UNIFORM_BUFFER, sceneMatrices);
	glBufferSubData(GL_UNIFORM_BUFFER, sizeof(mat4), sizeof(mat4), glm::value_ptr(viewMat));
	glBufferSubData(GL_UNIFORM_BUFFER, sizeof(mat4)*2,sizeof(vec3),glm::value_ptr(camera->getPos()));
	glBindBuffer(GL_UNIFORM_BUFFER,0);

	for (const auto& element : plottables) {
		//TODO: pop the invisible plottables off the vector instead of this horribleness
		if(element->isVisible()){
			element->draw();
		}
	
	}
}

Camera* Scene::getCamera() {
	return camera;
}
GLuint Scene::getSceneMatrices() {
	return sceneMatrices;
}