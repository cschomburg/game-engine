#ifndef CONVEX_H
#define CONVEX_H

#include <vector>

#include "Vector2.h"

class Rect;

class Convex {
public:
	Convex();
	virtual ~Convex();

	void translate(const Vector2 &pos);

	Rect boundingBox() const;
	Vector2 center() const;

	bool intersects(const Convex &other, Vector2 *collVector = 0);

	static Convex fromSize(const Vector2 &size);
	static Convex fromRect(const Rect &rect);

public:
	std::vector<Vector2> points;
};

#endif /* end of include guard: CONVEX_H */
