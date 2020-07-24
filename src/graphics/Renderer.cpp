#include "Renderer.h"

#include "Camera.h"
#include "AssetLoader.h"


#include "../computation/vectorfield.h"

#include <iostream>
#include "Shaders.h"


using namespace glm;



//TODO: Just for debugging purposes
VectorField* v;

Renderer::Renderer() :
	projectionMat(glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f)),
	modelMat(mat4(1.0f)),
	viewMat(rotate(mat4(1.0f), 1.0f, vec3(1.0, 0.0, 0.0)))
{

	//TODO: REMOVE
	v = new VectorField(0.1, 4, 0.1);

	this->arrowModel = new Model;
	Util::loadModel("arrowcone.obj",arrowModel->vertices, arrowModel->indices);
}


//Also debug stuff. Remove this and switch to shaders
const vec3 colors[3] = { vec3(1.0, 0.0, 0.0), vec3(0.0, 1.0, 0.0), vec3(0.0, 0.0, 1.0) };
const vec3 basiscolors[3] = {vec3(1.0,0.0,0.0), vec3(0.0,1.0,0.0), vec3(0.0,0.0,1.0)};
const vec4 basisvectors[3] = {vec4(1.0,0.0,0.0,1.0),vec4(0.0,1.0,0.0,1.0), vec4(0.0,0.0,1.0,1.0)};

void Renderer::initGL() {
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, arrowModel->vertices.size() * sizeof(vec3), &arrowModel->vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &elementbuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, arrowModel->indices.size() * sizeof(unsigned int), &arrowModel->indices[0], GL_STATIC_DRAW);
	programID = Util::loadShadersFromSource(CONE_VERTEXSHADER, CONE_FRAGMENTSHADER);
	mvpID = glGetUniformLocation(programID, "MVP");
	//glUseProgram(programID); //TODO: Maybe unneccessary
}

void Renderer::tempRender() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	this->drawAxes();

	glEnable(GL_POINT_SIZE);
	glPointSize(5.0);
	glBegin(GL_POINTS);

	const int cubicdim = v->getCubicDim();
	const int dim = cubicdim * cubicdim * cubicdim;
	for (int i = 0; i < dim; i++) {
		const Vector vec = v->getVector(i);
		vec4 transformedVector = projectionMat * viewMat * modelMat * vec4(vec.p.x, vec.p.z, vec.p.y, 1.0);
		glVertex3f(transformedVector.x, transformedVector.y, transformedVector.z);
	}
	glEnd();


	/*glUseProgram(programID);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);

	mat4 mvp = projectionMat * viewMat * modelMat;

	glUniformMatrix4fv(mvpID, 1, GL_FALSE, &mvp[0][0]);	//TODO: Perhaps change 1 to however many there are
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
		);

	glDrawElements(
		GL_TRIANGLES,
		arrowModel->indices.size(),
		GL_UNSIGNED_INT,
		(void*)0
		);
	glDisableVertexAttribArray(0);*/

}

void Renderer::drawArrow(Vector v) {
	std::cout << "TO BE ADDED!\n";
}

void Renderer::drawAxes() {
	vec4 transformedvertices[3];

	for (int i = 0; i < 3; i++) {
		transformedvertices[i] = projectionMat * viewMat * modelMat * basisvectors[i];
	}
	glBegin(GL_LINES);
	for (int i = 0; i < 3; i++) {
		const vec3 color = basiscolors[i];
		const vec4 vertex = basisvectors[i];
		glColor3f(color.r, color.g, color.b);
		glVertex3f(0.0, 0.0, 0.0);
		glVertex3f(transformedvertices[i].x, transformedvertices[i].y, transformedvertices[i].z);
	}
	glEnd();
}

void Renderer::multModel(mat4 matrix, bool fromRight) {
	if (fromRight) {
		modelMat = matrix * modelMat;
	}
	else {
		modelMat = modelMat * matrix;
	}
}

void Renderer::multView(mat4 matrix, bool fromRight) {
	if (fromRight) {
		viewMat = matrix * viewMat;
	}
	else {
		viewMat = viewMat * matrix;
	}
}

void Renderer::setModel(mat4 model) {
	this->modelMat = model;
}
void Renderer::setView(mat4 view) {
	this->viewMat = view;
}
mat4* Renderer::getModel() {
	return &this->modelMat;
}
mat4* Renderer::getView() {
	return &this->viewMat;
}