#include "components/Positionable.h"

Positionable::Positionable() {}
Positionable::~Positionable() {}

Vector2 Positionable::pos() const {
	return m_pos;
}

void Positionable::setPos(const Vector2 &pos) {
	m_pos = pos;
}

float Positionable::angle() const {
	return m_angle;
}

void Positionable::setAngle(float angle) {
	m_angle = angle;
}

Positionable::Ptr Positionable::anchor() const {
	return m_anchor;
}

void Positionable::setAnchor(Positionable::Ptr positionable) {
	m_anchor = positionable;
}

Vector2 Positionable::worldPos() const {
	if (!m_anchor) {
		return pos();
	}
	return m_anchor->worldPos() + pos();
}
