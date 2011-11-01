#include <cmath>
#include <iomanip>

#include "Vector2.h"

Vector2::Vector2(float x, float y) {
	this->x = x;
	this->y = y;
}

Vector2 Vector2::operator+(const Vector2 &vec) const {
	return Vector2(x + vec.x, y + vec.y);
}

Vector2 Vector2::operator-(const Vector2 &vec) const {
	return Vector2(x - vec.x, y - vec.y);
}

Vector2 Vector2::operator*(float t) const {
	return Vector2(t * x, t * y);
}

Vector2 Vector2::operator*(const Vector2 &vec) const {
	return Vector2(x * vec.x, y * vec.y);
}

Vector2 Vector2::operator/(float t) const {
	return Vector2(x / t, y / t);
}

float Vector2::dot(const Vector2 &vec) const {
	return (x * vec.x) + (y * vec.y);
}

void Vector2::operator+=(const Vector2 &vec) {
	x += vec.x;
	y += vec.y;
}

void Vector2::operator-=(const Vector2 &vec) {
	x -= vec.x;
	y -= vec.y;
}

void Vector2::operator*=(float t) {
	x *= t;
	y *= t;
}

void Vector2::operator/=(float t) {
	x /= t;
	y /= t;
}

void Vector2::operator=(const Vector2 &vec) {
	x = vec.x;
	y = vec.y;
}

bool Vector2::operator==(const Vector2 &vec) {
	return x == vec.x && y == vec.y;
}

bool Vector2::operator!=(const Vector2 &vec) {
	return x != vec.x || y != vec.y;
}

float Vector2::magnitude() const {
	return sqrtf(x*x + y*y);
}

bool Vector2::isZero() const {
	return x == 0 && y == 0;
}

void Vector2::normalize() {
	if (x == 0 && y == 0)
		return;

	float mag = magnitude();
	x /= mag;
	y /= mag;
}

Vector2 Vector2::normalized() const {
	Vector2 vec = *this;
	vec.normalize();
	return vec;
}

Vector2 Vector2::perpendicular() const {
	return Vector2(-y, x);
}

Vector2 Vector2::projected(const Vector2 &vec) const {
	Vector2 vecN = vec.normalized();
	return vecN * dot(vecN);
}

std::ostream& operator<<(std::ostream &o, const Vector2 &a) {
	return o << "[" << std::setprecision(2) << a.x << ", " << a.y << "]";
}
