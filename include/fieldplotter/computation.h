#pragma once
#include <fieldplotter/commonheaders.h>
#include <thread>
struct Point {
	float x, y, z;
	Point() : x(0), y(0), z(0) {}
	Point(float x, float y, float z) : x(x), y(y), z(z) {}
	
	const float magsq() {
		return x*x+y*y+z*z;
	}
	const float mag() {
		return sqrtf(x*x+y*y+z*z);	//sqrtf32 does not compile on Windows.
	}
	void operator+=(Point const& v);	//reference to const Point
	void operator-=(Point const& v);
	void operator*=(float scalar);
	void operator/=(float scalar);
	void operator=(Point const& c);
};
Point operator+(Point const& a, Point const& b);
Point operator-(Point const& a, Point const& b);
Point operator*(Point const& a, float scalar);
Point operator*(float scalar, Point const& a);
Point operator/(Point const& a, float scalar);
Point operator/(float scalar, Point const& a);
#include "point_operators.inl"

class Plottable;
struct PointCharge {
	Point p;
	float charge;
	PointCharge() : p(Point()),charge(0.0f){}
	PointCharge(Point p, float charge) : p(p), charge(charge) {}
	PointCharge(float x, float y, float z, float charge) : p(Point(x, y, z)), charge(charge) {}
};

class ChargeSystem;

//A wrapper for any ol' generic computation threa
template <typename T>
class Computation {
	private:
		T& plottable;
		ChargeSystem& charge_system;
		bool completed;
		void (*compute_function)(T& object, ChargeSystem& system);
		void run();
	protected:
		virtual void onFinalize() {}
	public:
		Computation(T& plottable,ChargeSystem& charge_system, void (*func)(T& object, ChargeSystem& system));
		std::thread spawnThread();
		bool isComplete(){return completed;}
};

//compute functions not contained within any class so that they may be more easily provided through other interfaces in the future (CUDA, Fortran, MATLAB,....)
class VectorField;
class FieldLines;
void compute_electric_field(VectorField& vf, ChargeSystem& system);
void compute_field_lines(FieldLines& lines, ChargeSystem& system);
Point electrical_force_at(Point r,ChargeSystem& system);