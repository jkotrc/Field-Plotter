#pragma once
#include <fieldplotter/commonheaders.h>


typedef struct Point {
	float x, y, z;
	Point() : x(0), y(0), z(0) {}
	Point(float x, float y, float z) : x(x), y(y), z(z) {}
} Point;



typedef struct PointCharge {
	Point p;
	float charge;
	PointCharge() : p(Point()),charge(0.0f){}
	PointCharge(Point p, float charge) : p(p), charge(charge) {}
	PointCharge(float x, float y, float z, float charge) : p(Point(x, y, z)), charge(charge) {}
} PointCharge;


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
		Model* arrowModel;

		float spatial_separation;
		int dimension;
		int N;
		float* vectors;	//array of vectors
		float* positions; //positions of the lattice
		float lowerBound;
		float upperBound;
    protected:
        void initGL() override;
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
		void setParent(Scene* parent) override;
};