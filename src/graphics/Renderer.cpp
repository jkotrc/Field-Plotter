#include "Renderer.h"

#include "Camera.h"

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc/quaternion.hpp>

#include <QTimer>

#include <iostream>
using namespace glm;
Renderer::Renderer()
{
	this->angle = 0.1f;
}

vec3 colors[3] = { vec3(1.0, 0.0, 0.0), vec3(0.0, 1.0, 0.0), vec3(0.0, 0.0, 1.0) };
vec4 vertices[3] = { vec4(-0.5, -0.5, 0,1.0) ,vec4(0.5, -0.5, 0.0,1.0),vec4(0.0, 0.5, 0.0,1.0)};



void Renderer::tempRender() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (int i = 0; i < 3; i++) {
		vertices[i] = rotate(mat4(1.0f), angle, vec3(1.0, 1.0, 0.0)) * vertices[i];
	}
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < 3; i++) {
		glColor3f(colors[i].r, colors[i].g, colors[i].b);
		glVertex3f(vertices[i].x, vertices[i].y, vertices[i].z);
	}
	glEnd();
}