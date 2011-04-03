#include "Positionable.h"
#include <SDL/SDL.h>

Positionable::Positionable(float x, float y) {
	m_pos = Vector2(x, y);
}

const Vector2 &Positionable::pos() const {
	return m_pos;
}

void Positionable::setPos(float x, float y) {
	m_pos.x = x;
	m_pos.y = y;
}

void Positionable::setPos(const Vector2 &pos) {
	m_pos = pos;
}

void Positionable::addPos(float x, float y) {
	m_pos.x += x;
	m_pos.y += y;
}

void Positionable::addPos(const Vector2 &pos) {
	m_pos += pos;
}
