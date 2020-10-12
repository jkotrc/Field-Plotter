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
	return Point(a.x/c, a.y/c, a.z/c);
}
inline Point operator/(float c, Point const& a){
	return Point(a.x/c, a.y/c, a.z/c);
}
inline void Point::operator=(Point const& c) {
	this->x=c.x;
	this->y=c.y;
	this->z=c.z;
}
inline void Point::operator+=(Point const& v) {
	this->x += v.x;
	this->y += v.y;
	this->z += v.z;
}
inline void Point::operator-=(Point const& v) {
	this->x -= v.x;
	this->y -= v.y;
	this->z -= v.z;
}
inline void Point::operator*=(float c) {
	this->x *= c;
	this->y *= c;
	this->z *= c;
}
inline void Point::operator/=(float c) {
	this->x /= c;
	this->y /= c;
	this->z /= c;
}