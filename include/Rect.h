#ifndef RECT_H
#define RECT_H

#include <algorithm>

#include "Vector2.h"

class Rect {
public:
	Rect(float x = 0, float y = 0, float w = 0, float h = 0);
	Rect(const Vector2 &pos, const Vector2 &size, bool centered = false);

	Vector2 pos() const;
	Vector2 size() const;
	void setPos(const Vector2 &pos);
	void addPos(const Vector2 &pos);
	void setSize(const Vector2 &pos);

	float left() const;
	float right() const;
	float top() const;
	float bottom() const;

	Vector2 center() const;

	bool intersects(const Rect &other) const;
	bool contains(const Vector2 &vec) const;

	Rect united(const Rect &other) const;
	Rect intersected(const Rect &other) const;

public:
	float x;
	float y;
	float w;
	float h;
};

#endif /* end of include guard: RECT_H */
