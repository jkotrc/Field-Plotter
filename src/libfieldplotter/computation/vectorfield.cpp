#include <fieldplotter/fieldplotter.h>
#include "../Debug.h"

#include <stdio.h>
#include <cmath>
/*
	Sweep x, then y, then z
	x,y,z = (0,0,0) corresponds to the point (-separation*dimension/2, -separation*dimension/2, -separation*dimension/2)

	So the origin is actually only present at even-dimensional vector fields at x,y,z = (N/2, N/2, N/2)
*/
VectorField::VectorField(float spatial_separation, int dimension)
	: 
	spatial_separation(spatial_separation),
	dimension(dimension),
	N(dimension*dimension*dimension)
{
	vectors = new float[3*N];
	positions = new float[3*N];

	//The coordinates of the corner-most vector in the cube. The loop goes from it to the other edge; chosen such that the cube is centered at (0,0,0)
	const float cornerVectorCoords = -spatial_separation * ((float)dimension - 1) / 2;	
	float x = cornerVectorCoords, y=x, z=x;
	
	for (int k = 0; k < 3*dimension; k+=3) {
		for (int j = 0; j < 3*dimension; j+=3) {
			for (int i = 0; i < 3*dimension; i+=3) {
				const int index = i+dimension*(j+dimension*k);

				vectors[index] = x*5.5;
				vectors[index+1]= y*5.5;
				vectors[index+2] = z*5.5;

				positions[index]=x;
				positions[index+1]=y;
				positions[index+2]=z;
				printf("doing vector number %u... that is indicies (%u,%u,%u)\n",index/3,index,index+1,index+2);
				printf("component vector: (%f,%f,%f)\n",vectors[index],vectors[index+1],vectors[index+2]);
				printf("position vector: (%f,%f,%f)\n",positions[index],positions[index+1],positions[index+2]);
				printf("magnitude: %f\n",((vectors[index]*vectors[index]+vectors[index+1]*vectors[index+1]+vectors[index+2]*vectors[index+2])-1.5f)/10.0f);
				x += spatial_separation;
			}
			x = cornerVectorCoords;
			y += spatial_separation;
		}
		x = cornerVectorCoords;
		y = cornerVectorCoords;
		z += spatial_separation;
	}
	Debug::debugString("VectorField","VF initialized");
}
VectorField::~VectorField() {
	Debug::debugString("VectorField", "destroying vector field");
	delete vectors;
	delete positions;
}
Point indexCoords(int i, int j, int k) {
	return Point(0,0,0);
}

void VectorField::getVectorComponentBuffer(GLuint* tag, int attribute_index) {
	if (glewInit() != GLEW_OK) {
		Debug::debugString("VectorField", "No valid OpenGL context!");
	}
	glGenBuffers(1, tag);
	glBindBuffer(GL_ARRAY_BUFFER, *tag);
	glEnableVertexAttribArray(attribute_index);
	glVertexAttribPointer(attribute_index, 3, GL_FLOAT, false, 0, nullptr);
	glVertexAttribDivisor(attribute_index,1);
	glBufferData(GL_ARRAY_BUFFER, this->N * sizeof(float)*3, vectors, GL_STATIC_DRAW);
}
void VectorField::getVectorPositionBuffer(GLuint* tag, int attribute_index) {
	if (glewInit() != GLEW_OK) {
		Debug::debugString("VectorField", "No valid OpenGL context!");
	}
	glGenBuffers(1, tag);
	glBindBuffer(GL_ARRAY_BUFFER, *tag);
	glEnableVertexAttribArray(attribute_index);
	glVertexAttribPointer(attribute_index, 3, GL_FLOAT, false, 0, nullptr);
	glVertexAttribDivisor(attribute_index,1);
	glBufferData(GL_ARRAY_BUFFER, this->N * sizeof(float)*3, positions, GL_STATIC_DRAW);
}

int VectorField::getDimension() {
	return dimension;
}
int VectorField::getAmount() {
	return dimension*dimension*dimension;
}

Vector VectorField::getVector(int index) {
	return Vector(vectors[index],vectors[index+1],vectors[index+2]);
}
Vector VectorField::getVector(Point p) {
	//TODO: Implement this properly
	return Vector(0.0f,0.0f,0.0f);
}