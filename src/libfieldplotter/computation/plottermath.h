#pragma once

#include <fieldplotter_pch.h>

typedef unsigned int GLuint;

struct Point {
	float x, y, z;
	Point() : x(0), y(0), z(0) {}
	Point(float x, float y, float z) : x(x), y(y), z(z) {}

	constexpr float magsq() const {
		return x * x + y * y + z * z;
	}
	const float mag() const {
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

struct PerspectiveParams {
    float aspect_ratio;
    float zNear;
    float zFar;
    float fov;
    PerspectiveParams() { //defaults
        aspect_ratio=1.0f;
        zNear=0.1f;
        zFar=100.0f;
        fov=glm::radians(45.0f);
    }
};

glm::mat4 makePerspective(PerspectiveParams parameters);

/*glm::mat4 makePerspective(PerspectiveParams parameters) {
	return ;
}*/