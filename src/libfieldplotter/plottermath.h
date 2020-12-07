#pragma once

#include <glm/glm.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtc/matrix_inverse.hpp>

typedef unsigned int GLuint;

struct Point {
	float x, y, z;
	Point() : x(0), y(0), z(0) {}
	Point(float x, float y, float z) : x(x), y(y), z(z) {}

	constexpr float magsq() const {
		return x * x + y * y + z * z;
	}
	constexpr float mag() const {
		return sqrtf(x * x + y * y + z * z);
	}

	void operator+=(Point const& v);	//reference to const Point
	void operator-=(Point const& v);
	void operator*=(float scalar);
	void operator/=(float scalar);
	void operator=(Point const& c);
	bool operator==(Point const& c);
};
Point operator+(Point const& a, Point const& b);
Point operator-(Point const& a, Point const& b);
Point operator*(Point const& a, float scalar);
Point operator*(float scalar, Point const& a);
Point operator/(Point const& a, float scalar);
Point operator/(float scalar, Point const& a);
#include "point_operators.inl"

struct PointCharge {
	Point p;
	float charge;
	PointCharge() : p(Point()), charge(0.0f) {}
	PointCharge(Point p, float charge) : p(p), charge(charge) {}
	PointCharge(float x, float y, float z, float charge) : p(Point(x, y, z)), charge(charge) {}
};