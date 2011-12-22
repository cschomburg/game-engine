#include "Box2DCompat.h"

b2Vec2 toBox2D(const Vector2 &vec) {
	return b2Vec2(vec.x, vec.y);
}

Vector2 fromBox2D(const b2Vec2 &vec) {
	return Vector2(vec.x, vec.y);
}
