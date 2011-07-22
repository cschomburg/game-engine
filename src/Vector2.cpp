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

void Vector2::normalize() {
	if (x == 0 && y == 0)
		return;

	float mag = magnitude();
	x /= mag;
	y /= mag;
}

bool Vector2::isZero() const {
	return x == 0 && y == 0;
}

std::ostream& operator<<(std::ostream &o, const Vector2 &a) {
	return o << "[" << std::setprecision(2) << a.x << ", " << a.y << "]";
}
