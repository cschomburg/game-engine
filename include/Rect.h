#ifndef RECT_H
#define RECT_H

#include "Vector2.h"

enum class Anchor {
	topLeft,
	top,
	topRight,
	left,
	center,
	right,
	bottomLeft,
	bottom,
	bottomRight,
};

class Rect {
public:
	Rect();
	Rect(const Vector2 &pos, const Vector2 &size, Anchor anchor = Anchor::center);

	Vector2 pos(Anchor anchor = Anchor::center) const;
	void setPos(const Vector2 &pos, Anchor anchor = Anchor::center);
	void translate(const Vector2 &pos);

	Vector2 size() const;
	void setSize(const Vector2 &pos);
	void scale(float factor);

	float left() const;
	float right() const;
	float top() const;
	float bottom() const;

	bool intersects(const Rect &other) const;
	bool contains(const Vector2 &point) const;
	bool contains(const Rect &other) const;

	Rect united(const Rect &other) const;
	Rect intersected(const Rect &other) const;

private:
	float x;
	float y;
	float hw;
	float hh;
};

#endif /* end of include guard: RECT_H */
