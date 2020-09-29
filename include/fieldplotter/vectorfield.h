#pragma once
#include <fieldplotter/commonheaders.h>
#include <fieldplotter/plottable.h>
#include <fieldplotter/computation.h>

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
//TODO: Integrate this with computational code  
//class Plottable;
class Plottable;
class VectorField: public Plottable {
	private:
		float spatial_separation;
		int dimension;
		int N;
		float* vectors;	//array of vectors
		float* positions; //positions of the lattice
		float lowerBound;
		float upperBound;
		enum VectorField_Buffers {FP_POSITION=3,FP_COMPONENT};
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
		void draw() override;
		void initGraphics();
};