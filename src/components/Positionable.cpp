#include "components/Positionable.h"

const ComponentType Positionable::componentType = "Positionable";

Positionable::Positionable(Object *object)
	: Component(componentType, object) {}

Positionable::~Positionable() {}

Vector2 Positionable::pos() const {
	return m_pos;
}

void Positionable::setPos(const Vector2 &pos) {
	m_pos = pos;
}

void Positionable::modifyPos(const Vector2 &pos) {
	m_pos += pos;
}
