#include <SDL/SDL_opengl.h>

#include <algorithm>
#include <limits>

#include "Polygon.h"
#include "Rect.h"

Polygon::Polygon() {}

Polygon::~Polygon() {}

Rect Polygon::boundingBox() const {
	if (points.size() == 0)
		return Rect();

	float xMin = std::numeric_limits<float>::max();
	float yMin = std::numeric_limits<float>::min();
	float xMax = -xMin;
	float yMax = -yMin;

	for (std::vector<Vector2>::const_iterator i = points.begin(); i != points.end(); ++i) {
		xMin = std::min(xMin, i->x);
		xMax = std::max(xMax, i->x);
		yMin = std::min(yMin, i->y);
		yMax = std::max(yMax, i->y);
	}

	return Rect(xMin, yMin, xMax-xMin, yMax-yMin);
}

Vector2 Polygon::center() const {
	if (points.size() == 0)
		return Vector2();

	float sX = 0;
	float sY = 0;
	for (std::vector<Vector2>::const_iterator i = points.begin(); i != points.end(); ++i) {
		sX += i->x;
		sY += i->y;
	}
	return Vector2(sX/points.size(), sY/points.size());
}

Polygon Polygon::fromSize(const Vector2 &size) {
	Polygon poly;
	poly.points.reserve(4);
	poly.points.push_back(Vector2(-size.x/2, -size.y/2));
	poly.points.push_back(Vector2(size.x/2, -size.y/2));
	poly.points.push_back(Vector2(size.x/2, size.y/2));
	poly.points.push_back(Vector2(-size.x/2, size.y/2));
	return poly;
}

Polygon Polygon::fromRect(const Rect &rect) {
	Polygon poly;
	poly.points.reserve(4);
	poly.points.push_back(rect.bottomLeft());
	poly.points.push_back(rect.bottomRight());
	poly.points.push_back(rect.topRight());
	poly.points.push_back(rect.topLeft());
	return poly;
}

void Polygon::translate(const Vector2 &pos) {
	for (std::vector<Vector2>::iterator i = points.begin(); i != points.end(); ++i) {
		(*i) += pos;
	}
}

bool Polygon::intersects(const Polygon &other, Vector2 *collVector) {
	Vector2 minAxis;
	float minDistance = std::numeric_limits<float>::max();

	int p1Size = points.size();
	int p2Size = other.points.size();

	// Iterate through all axes of object 1 and 2
	for (int i = 0; i < p1Size+p2Size; i++) {

		// Get the edge 
		Vector2 axis;
		if (i < p1Size) { // Object 1
			axis = points[i] - points[(i+1) % p1Size];
		} else { // Object 2
			int pI = i-p1Size;
			axis = other.points[pI] - other.points[(pI+1) % p2Size];
		}
		axis.y = -axis.y; // Create axis perpendicular to edge
		axis.normalize();

		// Project object 1 onto axis
		float min1 = std::numeric_limits<float>::max();
		float max1 = -min1;
		for (int j = 0; j < p1Size; j++) {
			float dot = axis.dot(points[j]);
			min1 = std::min(min1, dot);
			max1 = std::max(max1, dot);
		}

		// Project object 2 onto axis
		float min2 = std::numeric_limits<float>::max();
		float max2 = -min2;
		for (int j = 0; j < p2Size; j++) {
			float dot = axis.dot(other.points[j]);
			min2 = std::min(min2, dot);
			max2 = std::max(max2, dot);
		}

		// Calculate distance between projections
		float distance = 0;
		if (min1 < min2) {
			distance = min2 - max1;
		} else {
			distance = min1 - max2;
		}

		// Distance greater zero -> no collision
		if (distance > 0.0f)
			return false;

		// Find smallest collision vector
		distance = -distance;
		if (distance < minDistance) {
			minDistance = distance;
			minAxis = axis;
		}
	}

	// Return collision vector
	if (collVector) {
		Vector2 dist = center() - other.center();
		if (dist.dot(minAxis) < 0) // Orient vector outwards
			minAxis *= -1;
		*collVector = minAxis * minDistance;
	}

	return true;
}
