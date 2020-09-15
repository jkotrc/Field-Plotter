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

				//vectors[index] = x*5.5;
				//vectors[index+1]= y*5.5;
				//vectors[index+2] = z*5.5;

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
	Debug::debugString("VectorField","VF initialized");
}
VectorField::~VectorField() {
	Debug::debugString("VectorField", "destroying vector field");
	delete vectors;
	delete positions;
}


//broken
Point* VectorField::getPoint(int idx) {
	const float cornerVectorCoords = -spatial_separation * ((float)dimension - 1) / 2;
	Point ret = Point(cornerVectorCoords, cornerVectorCoords, cornerVectorCoords);
	
	//converts a linear index that goes from 0...N^3 into a cubic index (k,j,i)
	int index = idx;
	const int div = dimension;
	int k = index / (dimension * dimension);
	index = index % (dimension * dimension);
	int j = index / dimension;
	int i = index % dimension;
	//then uses it to find x,y,z based on spatial separation

	ret.x += spatial_separation * i;
	ret.y += spatial_separation * j;
	ret.z += spatial_separation * k;
	return &ret;
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
	return Vector(&positions[3*index],&vectors[3*index]);
}
Vector VectorField::getVector(Point p) {
	//TODO: Implement this properly
	return Vector(0,0);
	//return Vector();
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