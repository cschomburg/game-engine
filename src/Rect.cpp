#include <algorithm>

#include "Rect.h"

Rect::Rect() {
	x  = 0.0f;
	y  = 0.0f;
	hw = 0.0f;
	hh = 0.0f;
}

Rect::Rect(const Vector2 &pos, const Vector2 &size, Anchor anchor) {
	setPos(pos, anchor);
	setSize(size);
}

Vector2 Rect::pos(Anchor anchor) const {
	switch (anchor) {
	default: case Anchor::center: return Vector2(x,    y);
	case Anchor::topLeft:         return Vector2(x-hw, y+hh);
	case Anchor::top:             return Vector2(x,    y+hh);
	case Anchor::topRight:        return Vector2(x+hw, y+hh);
	case Anchor::left:            return Vector2(x-hw, y);
	case Anchor::right:           return Vector2(x+hw, y);
	case Anchor::bottomLeft:      return Vector2(x-hw, y-hh);
	case Anchor::bottom:          return Vector2(x,    y-hh);
	case Anchor::bottomRight:     return Vector2(x+hw, y-hh);
	}
}

void Rect::setPos(const Vector2 &pos, Anchor anchor) {
	switch (anchor) {
	default: case Anchor::center: x = pos.x;    y = pos.y;    break;
	case Anchor::topLeft:         x = pos.x-hw; y = pos.y+hh; break;
	case Anchor::top:             x = pos.x;    y = pos.y+hh; break;
	case Anchor::topRight:        x = pos.x;    y = pos.y+hh; break;
	case Anchor::left:            x = pos.x-hh; y = pos.y;    break;
	case Anchor::right:           x = pos.x+hh; y = pos.y;    break;
	case Anchor::bottomLeft:      x = pos.x-hh; y = pos.y-hh; break;
	case Anchor::bottom:          x = pos.x;    y = pos.y-hh; break;
	case Anchor::bottomRight:     x = pos.x+hh; y = pos.y-hh; break;
	}
}

void Rect::translate(const Vector2 &pos) {
	x += pos.x;
	y += pos.y;
}

Vector2 Rect::size() const {
	return Vector2(hw*2.0f, hh*2.0f);
}

void Rect::setSize(const Vector2 &size) {
	hw = size.x/2.0f;
	hh = size.y/2.0f;
}

void Rect::scale(float factor) {
	hw *= factor;
	hh *= factor;
}

float Rect::left()   const { return x-hw; }
float Rect::right()  const { return x+hw; }
float Rect::top()    const { return y+hh; }
float Rect::bottom() const { return y-hh; }

bool Rect::intersects(const Rect &other) const {
	return !(  (left() > other.right() )
			|| (right() < other.left() )
			|| (top() < other.bottom() )
			|| (bottom() > other.top() ));
}

bool Rect::contains(const Vector2 &point) const {
	return (   (point.x > left())
		    && (point.y > bottom())
		    && (point.x < right())
		    && (point.y < top()));
}

bool Rect::contains(const Rect &other) const {
	return (   (left() < other.left())
			&& (right() > other.right())
			&& (top() > other.top())
			&& (bottom() < other.bottom()));
}

Rect Rect::united(const Rect &other) const {
	float l = std::min(left(), other.left());
	float b = std::min(bottom(), other.bottom());
	float r = std::max(right(), other.right());
	float t = std::max(top(), other.top());
	float w = r-l;
	float h = t-b;

	return Rect(Vector2(l+w/2.0f, b+h/2.0f), Vector2(w, h), Anchor::center);
}

Rect Rect::intersected(const Rect &other) const {
	if (!intersects(other))
		return Rect();

	float l = std::max(left(), other.left());
	float b = std::max(bottom(), other.bottom());
	float r = std::min(right(), other.right());
	float t = std::min(top(), other.top());
	float w = r-l;
	float h = t-b;

	return Rect(Vector2(l+w/2.0f, b+h/2.0f), Vector2(w, h), Anchor::center);
}
