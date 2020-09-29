#pragma once
#include <fieldplotter/commonheaders.h>

struct Point {
	float x, y, z;
	Point() : x(0), y(0), z(0) {}
	Point(float x, float y, float z) : x(x), y(y), z(z) {}
	Point operator+(const Point& b) {
		return Point(this->x+b.x,this->y+b.y,this->z+b.z);
	}
	Point operator-(const Point&b) {
		return Point(this->x-b.x,this->y-b.y,this->z-b.z);
	}
	const Point operator*(const float c) {
		return Point(c*this->x, c*this->y, c*this->z);
	}
	Point operator/(const float c) {
		return Point(c/this->x, c/this->y, c/this->z);
	}
	const float mag() {
		return x*x+y*y+z*z;
	}
	const float magsq() {
		return sqrtf32(x*x+y*y+z*z);
	}
};

class Plottable;
struct PointCharge {
	Point p;
	float charge;
	PointCharge() : p(Point()),charge(0.0f){}
	PointCharge(Point p, float charge) : p(p), charge(charge) {}
	PointCharge(float x, float y, float z, float charge) : p(Point(x, y, z)), charge(charge) {}
};

class VectorField;
class FieldLines;
class ChargeSystem;
typedef struct {	//TODO: Refactor this into ChargeSystem
	PointCharge* charges;
	int n_charges;
} PhysicsConfiguration;

//compute functions not contained within the classes because of the intention of things like VectorField to be applicable to other physical systems
void compute_electric_field(VectorField& vf, ChargeSystem& system);
void compute_field_lines(FieldLines& lines, ChargeSystem& system);
Point electrical_force_at(Point r,ChargeSystem& system);