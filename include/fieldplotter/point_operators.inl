#pragma once

inline Point operator+(Point const& a, Point const& b) {
	return Point(a.x + b.x, a.y + b.y, a.z + b.z);
}
inline Point operator-(Point const& a, Point const& b) {
	return Point(a.x - b.x, a.y - b.y, a.z - b.z);
}
inline Point operator*(Point const& a, float c){
	return Point(c * a.x, c * a.y, c * a.z);
}
inline Point operator*(float c, Point const& a){
	return Point(c * a.x, c * a.y, c * a.z);
}
inline Point operator/(Point const& a, float c){
	return Point(c / a.x, c / a.y, c / a.z);
}
inline Point operator/(float c, Point const& a){
	return Point(c / a.x, c / a.y, c / a.z);
}
inline Point& Point::operator+=(Point const& v) {
	this->x += v.x;
	this->y += v.y;
	this->z += v.z;
}
inline Point& Point::operator-=(Point const& v) {
	this->x -= v.x;
	this->y -= v.y;
	this->z -= v.z;
}
inline Point& Point::operator*=(float c) {
	this->x *= c;
	this->y *= c;
	this->z *= c;
}
inline Point& Point::operator/=(float c) {
	this->x /= c;
	this->y /= c;
	this->z /= c;
}
