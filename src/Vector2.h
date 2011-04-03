#include "Vector2.h"

Vector2::Vector2(float x, float y) {
	this->x = x;
	this->y = y;
}

Vector2 operator+(const Vector &vec) {
	return Vector2(x + vec.x, y + vec.y);
}

Vector2 operator-(const Vector &vec) {
	return Vector2(x - vec.x, y - vec.x);
}

Vector2 operator*(float t) {
	return Vector2(t * x, t * y);
}

Vector2 operator/(float t) {
	return Vector2(x / t, y / t);
}

void operator+(const Vector2 &vec) {
	x += vec.x;
	y += vec.y;
}

void operator-(const Vector2 &vec) {
	x -= vec.x;
	y -= vec.y;
}

void operator*(float t) {
	x *= t;
	y *= t;
}

void operator/(float t) {
	x /= t;
	y /= t;
}

void operator=(const Vector2 &vec) {
	x = vec.x;
	y = vec.y;
}

void operator==(const Vector2 &vec) {
	return x == vec.x && y == vec.y;
}

void operator!=(const Vector2 &vec) {
	return x != vec.x || y != vec.y;
}
