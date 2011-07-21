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

Vector2 Vector2::normalize() const {
	float mag = magnitude();
	if (mag == 0)
		return Vector2(0 ,0);
	return Vector2(x/mag, y/mag);
}

std::ostream& operator<<(std::ostream &o, const Vector2 &a) {
	return o << "[" << std::setprecision(2) << a.x << ", " << a.y << "]";
}
