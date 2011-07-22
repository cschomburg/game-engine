#include "Rect.h"

Rect::Rect(float x, float y, float w, float h) {
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
}

Rect::Rect(const Vector2 &pos, const Vector2 &size, bool centered) {
	if (centered) {
		setPos(pos - size/2);
	} else {
		setPos(pos);
	}
	setSize(size);
}

Vector2 Rect::pos() const {
	return Vector2(x, y);
}

void Rect::setPos(const Vector2 &pos, bool centered) {
	if (centered) {
		x = pos.x - w/2;
		y = pos.y - h/2;
	} else {
		x = pos.x;
		y = pos.y;
	}
}

void Rect::translate(const Vector2 &pos) {
	x += pos.x;
	y += pos.y;
}

Vector2 Rect::size() const {
	return Vector2(w, h);
}

void Rect::setSize(const Vector2 &size) {
	w = size.x;
	h = size.y;
}

float Rect::left() const { return x; }
float Rect::right() const { return x + w; }
float Rect::top() const { return y + h; }
float Rect::bottom() const { return y; }

Vector2 Rect::center() const {
	return pos() + size()/2;
}

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
	float nX = std::min(x, other.x);
	float nY = std::min(y, other.y);
	float nX2 = std::max(x + w, other.x + other.w);
	float nY2 = std::max(y + h, other.y + other.y);

	return Rect(nX, nY, nX2-nX, nY2-nY);
}

Rect Rect::intersected(const Rect &other) const {
	if (!intersects(other))
		return Rect();

	float nX = std::max(x, other.x);
	float nY = std::max(y, other.y);
	float nX2 = std::min(x + w, other.x + other.w);
	float nY2 = std::min(y + h, other.y + other.y);

	return Rect(nX, nY, nX2-nX, nY2-nY);
}