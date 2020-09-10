#include "vectorfield.h"


/*
	Sweep x, then y, then z
	x,y,z = (0,0,0) corresponds to the point (separation*dimension/2, separation*dimension/2, separation*dimension/2)

	So the origin is actually only present at even-dimensional vector fields at x,y,z = (N/2, N/2, N/2)
*/

#define INDEX(i,j,k) i+cubic_dimension*(j+cubic_dimension*k)

VectorField::VectorField(double spatial_separation, int cubic_dimension, double visible_separation)		//make the default vector field just a radial vector field F = -P (i,j,k)
	: 
	spatial_separation(spatial_separation), 
	dimension(cubic_dimension), 
	visible_separation(visible_separation)
{
	const int dimension = cubic_dimension * cubic_dimension * cubic_dimension;
	this->vectors = new Vector[dimension];
	
	//The coordinates of the corner-most vector in the cube. The loop goes from it to the other edge; chosen such that the cube is centered at (0,0,0)
	const double cornerVectorCoords = -spatial_separation * ((double)cubic_dimension - 1) / 2;	
	double x = cornerVectorCoords, y=x, z=x;
	
	for (int k = 0; k < cubic_dimension; k++) {
		for (int j = 0; j < cubic_dimension; j++) {
			for (int i = 0; i < cubic_dimension; i++) {
				//TODO: this is a horrible way of doing it
				Vector v = Vector(x, y, z, -x, -y, -z);
				this->vectors[INDEX(i,j,k)] = v;
				x += spatial_separation;
			}
			x = cornerVectorCoords;
			y += spatial_separation;
		}
		x = cornerVectorCoords;
		y = cornerVectorCoords;
		z += spatial_separation;
	}
}

int VectorField::getCubicDim() {
	return dimension;
}
Vector VectorField::getVector(int index) {
	return this->vectors[index];
}