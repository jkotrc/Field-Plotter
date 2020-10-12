#pragma once
#include "plottermath.h"
#include "physicalobject.h"

//a wrapper struct with pointers to the point and components of some vector in a buffer
struct Vector {
	Point* pos;
	Point* component;
	Vector(Point* pos, Point* component) : pos(pos),component(component) {}
	float mag() {
		return component->mag();
	}
};
/*
 * A vector field class that creates a N*N*N dimensional cube of vectors, each separated by a certain spatial distance
*/

class VectorField: public PhysicalObject {
	private:
		float spatial_separation;
		int dimension;
		int model_size;
		int N;
		float* vectors;	//array of vectors
		float* positions; //positions of the lattice
		float lowerBound;
		float upperBound;
		enum VectorField_Buffers {FP_POSITION=3,FP_COMPONENT};
		void staticDraw() override;
		void dynamicDraw() override;
	public:
		VectorField(float separation, int cubic_dimension);
		~VectorField();
		Vector getVector(int index);	//Return vector pointer at index of an array
		void setVector(Vector v);
		int getDimension();
		int getAmount();
		float getUpperBound();
		float getLowerBound();
		void setUpperBound(float ub);
		void setLowerBound(float lb);
		void initGraphics() override;
};