#pragma once



typedef struct Point {
	double x, y, z;
	Point() : x(0), y(0), z(0) {}
	Point(double x, double y, double z) : x(x), y(y), z(z) {}
} Point;

typedef struct PointCharge {
	Point p;
	double charge;
	PointCharge(Point p, double charge) : p(p), charge(charge) {}
	PointCharge(double x, double y, double z, double charge) : p(Point(x, y, z)), charge(charge) {}
} PointCharge;

typedef struct Vector {
	Point p; //vector coordinates
	double i, j, k;	//vector components
	Vector() : p(Point()), i(0), j(0), k(0) {}
	Vector(Point p, double i, double j, double k) : p(p), i(i), j(j), k(k) {}
	Vector(double x, double y, double z, double i, double j, double k) : p(Point(x, y, z)), i(i), j(j), k(k) {}
} Vector;



/*
 * A vector field class that creates a N*N*N dimensional cube of vectors, each separated by a certain spatial distance
*/
class VectorField {
	private:
		//TODO: Convert spatial and visible separations to a single "separation" value, calculated by the user-inputted scale
		double spatial_separation;
		float visible_separation;
		int dimension;
		Vector* vectors;	//array of vectors

	public:
		VectorField(double spatial_seperation, int cubic_dimension, double visible_separation);
		Vector getVectorAt(Point p);	//Return vector at Point p
		Vector getVector(int index);	//Return vector at index of an array
		void setVector(Vector v);
		void setVectorAt(Point p, double i, double j, double k);
		int getCubicDim();

};