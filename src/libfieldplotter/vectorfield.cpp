#include "vectorfield.h"
#include "graphics.h"

#include "Shaders.h"
#include <stdio.h>
#include <cmath>
/*
	Sweep x, then y, then z
	x,y,z = (0,0,0) corresponds to the point (-separation*dimension/2, -separation*dimension/2, -separation*dimension/2)

	So the origin is actually only present at even-dimensional vector fields at x,y,z = (N/2, N/2, N/2)
*/
using namespace glm;
VectorField::VectorField(float spatial_separation, int dimension)
	:
	spatial_separation(spatial_separation),
	dimension(dimension),
	N(dimension*dimension*dimension)
{
	graphicsInitialized = false;
	//TODO: make this work
	setComputationalState(false);

	vectors = new float[3*N];
	positions = new float[3*N];
	
	//The coordinates of the corner-most vector in the cube. The loop goes from it to the other edge; chosen such that the cube is centered at (0,0,0)
	const float cornerVectorCoords = -spatial_separation * ((float)dimension - 1) / 2;	
	float x = cornerVectorCoords, y=x, z=x;
	
	for (int k = 0; k < 3*dimension; k+=3) {
		for (int j = 0; j < 3*dimension; j+=3) {
			for (int i = 0; i < 3*dimension; i+=3) {
				const int index = i+dimension*(j+dimension*k);
				vectors[index] = 0;
				vectors[index + 1] = 1;
				vectors[index + 2] = 0;

				positions[index]=x;
				positions[index+1]=y;
				positions[index+2]=z;
				x += spatial_separation;
			}
			x = cornerVectorCoords;
			y += spatial_separation;
		}
		x = cornerVectorCoords;
		y = cornerVectorCoords;
		z += spatial_separation;
	}
	lowerBound=0.0f;
	upperBound=1.0f;

}

VectorField::~VectorField() {
	delete vectors;
	delete positions;
}



void VectorField::initGraphics() {

	if (graphicsInitialized) return;
    modelMatrix=mat4(1.0f);
	Model model = loadArrowModel();
	model_size = model.indices.size();

	buffers.resize(5);

	glGenBuffers(1, &buffers[FP_VERTICES]);
	glBindBuffer(GL_ARRAY_BUFFER, buffers[FP_VERTICES]);
	glEnableVertexAttribArray(FP_VERTICES);
	glVertexAttribPointer(FP_VERTICES, 3, GL_FLOAT, false, 0, nullptr);
	glBufferData(GL_ARRAY_BUFFER, model.vertices.size() * sizeof(vec3), &model.vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &buffers[FP_NORMALS]);
	glBindBuffer(GL_ARRAY_BUFFER, buffers[FP_NORMALS]);
	glEnableVertexAttribArray(FP_NORMALS);
	glVertexAttribPointer(FP_NORMALS, 3, GL_FLOAT, false, 0, nullptr);
	glBufferData(GL_ARRAY_BUFFER, model.normals.size() * sizeof(vec3), &model.normals[0], GL_STATIC_DRAW);

	glGenBuffers(1, &buffers[FP_ELEMENTS]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[FP_ELEMENTS]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.indices.size() * sizeof(unsigned int), &model.indices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &buffers[VectorField::FP_POSITION]);
	glBindBuffer(GL_ARRAY_BUFFER, buffers[VectorField::FP_POSITION]);
	glEnableVertexAttribArray(VectorField::FP_POSITION);
	glVertexAttribPointer(VectorField::FP_POSITION, 3, GL_FLOAT, false, 0, nullptr);
	glVertexAttribDivisor(VectorField::FP_POSITION,1);
	glBufferData(GL_ARRAY_BUFFER, N * sizeof(float)*3, positions, GL_STATIC_DRAW);

	glGenBuffers(1, &buffers[VectorField::FP_COMPONENT]);
	glBindBuffer(GL_ARRAY_BUFFER, buffers[VectorField::FP_COMPONENT]);
	glEnableVertexAttribArray(VectorField::FP_COMPONENT);
	glVertexAttribPointer(VectorField::FP_COMPONENT, 3, GL_FLOAT, false, 0, nullptr);
	glVertexAttribDivisor(VectorField::FP_COMPONENT,1);
	glBufferData(GL_ARRAY_BUFFER, N * sizeof(float)*3, vectors, GL_STATIC_DRAW);

    programID = loadShadersFromSource(Shaders::ARROW_VERTEXSHADER, Shaders::ARROW_FRAGMENTSHADER);
	glUseProgram(programID);

	if (parent != NULL) {
		glUniformBlockBinding(programID, glGetUniformBlockIndex(programID, "Matrices"), 0);
		glBindBufferBase(GL_UNIFORM_BUFFER, 0, parent->getSceneMatrices());
		glUniformMatrix4fv(glGetUniformLocation(programID, "modelMat"), 1, false, glm::value_ptr(modelMatrix));
	}
	glUniform1f(glGetUniformLocation(programID, "lowerBound"), lowerBound);
	glUniform1f(glGetUniformLocation(programID, "upperBound"), upperBound);
	graphicsInitialized = true;
}

inline void VectorField::staticDraw() {
	glUseProgram(programID);
	glUniformBlockBinding(programID, glGetUniformBlockIndex(programID, "Matrices"), 0);
	glUniformMatrix4fv(glGetUniformLocation(programID, "modelMat"),1,false,glm::value_ptr(modelMatrix));
	glUniform1f(glGetUniformLocation(programID, "lowerBound"), lowerBound);
	glUniform1f(glGetUniformLocation(programID, "upperBound"), upperBound);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[FP_ELEMENTS]);

	glBindBuffer(GL_ARRAY_BUFFER, buffers[FP_VERTICES]);
	glVertexAttribPointer(FP_VERTICES, 3, GL_FLOAT, false, 0, nullptr);

	glBindBuffer(GL_ARRAY_BUFFER, buffers[FP_NORMALS]);
	glVertexAttribPointer(FP_NORMALS, 3, GL_FLOAT, false, 0, nullptr);

	glBindBuffer(GL_ARRAY_BUFFER, buffers[VectorField::FP_POSITION]);
	glVertexAttribPointer(VectorField::FP_POSITION, 3, GL_FLOAT, false, 0, nullptr);

	glBindBuffer(GL_ARRAY_BUFFER, buffers[VectorField::FP_COMPONENT]);
	glVertexAttribPointer(VectorField::FP_COMPONENT, 3, GL_FLOAT, false, 0, nullptr);

	glDrawElementsInstanced(GL_TRIANGLES,model_size,GL_UNSIGNED_INT,(void*)0,N);	
}

void VectorField::dynamicDraw() {

}

int VectorField::getDimension() {
	return dimension;
}
int VectorField::getAmount() {
	return dimension*dimension*dimension;
}

Vector VectorField::getVector(int index) {
	return Vector((Point*)&positions[3*index],(Point*)&vectors[3*index]);
}

float VectorField::getUpperBound() {
	return upperBound;
}
float VectorField::getLowerBound() {
	return lowerBound;
}
void VectorField::setUpperBound(float ub) {
	upperBound = ub;
}
void VectorField::setLowerBound(float lb) {
	lowerBound = lb;
}