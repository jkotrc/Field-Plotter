#include "Renderer.h"

#include "Camera.h"

#include <GL/glew.h>
#include <QTimer>
#include <iostream>

using namespace glm;
Renderer::Renderer()
{
	this->angle = 0.1f;
	
	this->Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
	this->Model =  mat4(1.0f);
	this->View = rotate(mat4(1.0f), 1.0f, vec3(1.0, 0.0, 0.0));
	
}

vec3 colors[3] = { vec3(1.0, 0.0, 0.0), vec3(0.0, 1.0, 0.0), vec3(0.0, 0.0, 1.0) };
vec4 vertices[3] = { vec4(-0.5, -0.5, 0,1.0) ,vec4(0.5, -0.5, 0.0,1.0),vec4(0.0, 0.5, 0.0,1.0)};



void Renderer::tempRender() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	vec4 transformedvertices[3];
	std::copy(std::begin(vertices), std::end(vertices), std::begin(transformedvertices));

	for (int i = 0; i < 3; i++) {
		transformedvertices[i] = Projection * View * Model * vertices[i];
	}

	glBegin(GL_TRIANGLES);
	for (int i = 0; i < 3; i++) {
		glColor3f(colors[i].r, colors[i].g, colors[i].b);
		glVertex3f(transformedvertices[i].x, transformedvertices[i].y, transformedvertices[i].z);
	}
	glEnd();
}

void Renderer::multModel(mat4 matrix, bool fromRight) {
	if (fromRight) {
		Model = matrix * Model;
	}
	else {
		Model = Model * matrix;
	}
}

void Renderer::multView(mat4 matrix, bool fromRight) {
	if (fromRight) {
		View = matrix * View;
	}
	else {
		View = View * matrix;
	}
}

void Renderer::setModel(mat4 model) {
	this->Model = model;
}
void Renderer::setView(mat4 view) {
	this->View = view;
}
mat4* Renderer::getModel() {
	return &this->Model;
}
mat4* Renderer::getView() {
	return &this->View;
}