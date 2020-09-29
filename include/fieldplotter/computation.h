#pragma once
#include <fieldplotter/commonheaders.h>

class Plottable;
struct PointCharge {
	Point p;
	float charge;
	PointCharge() : p(Point()),charge(0.0f){}
	PointCharge(Point p, float charge) : p(p), charge(charge) {}
	PointCharge(float x, float y, float z, float charge) : p(Point(x, y, z)), charge(charge) {}
};

class VectorField;
typedef struct {	//TODO: Refactor this into ChargeSystem
	PointCharge* charges;
	int n_charges;
} PhysicsConfiguration;

void compute_electric_field(VectorField& vf, ChargeSystem& system);


