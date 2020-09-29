#pragma once
#include <fieldplotter/commonheaders.h>
#include <fieldplotter/plottable.h>

typedef struct Point {
	float x, y, z;
	Point() : x(0), y(0), z(0) {}
	Point(float x, float y, float z) : x(x), y(y), z(z) {}
} Point;


//a wrapper struct with pointers to the point and components of some vector
#define SQUARE(A) (A)*(A)
typedef struct Vector {
	float* pos;
	float* component;
	Vector(float* pos, float* component) : pos(pos),component(component) {}
	float magnitude() {
		const float x = component[0];
		const float y = component[1];
		const float z = component[2];
		return (float)sqrt(x*x+y*y+z*z);
	}
} Vector;


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
		Vector getVector(Point p);	//Return vector at Point p
		Vector getVector(int index);	//Return vector pointer at index of an array
		Point* getPoint(int index);
		void setVector(Vector v);
		void setVectorAt(Point p, float i, float j, float k);
		int getDimension();
		int getAmount();
		float getUpperBound();
		float getLowerBound();
		void setUpperBound(float ub);
		void setLowerBound(float lb);
		void draw() override;
		void initGraphics();
};