#ifndef POLYGON_H
#define POLYGON_H

#include <vector>

#include "Vector2.h"

class Rect;

class Polygon {
public:
	Polygon();
	virtual ~Polygon();

	void translate(const Vector2 &pos);

	Rect boundingBox() const;
	Vector2 center() const;

	bool intersects(const Polygon &other, Vector2 *collVector = 0);

	static Polygon fromSize(const Vector2 &size);
	static Polygon fromRect(const Rect &rect);

public:
	std::vector<Vector2> points;
};

#endif /* end of include guard: POLYGON_H */
