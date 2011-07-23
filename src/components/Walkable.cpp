#include "components/Movable.h"
#include "components/Walkable.h"

const ComponentType Walkable::componentType = "Walkable";

Walkable::Walkable(Object *object)
	: Component(componentType, object) {}

Walkable::~Walkable() {}

void Walkable::setDirection(const Vector2 &direction) {
	m_direction = direction;
	m_direction.normalize();
}

void Walkable::setAcceleration(const Vector2 &acceleration) {
	m_acceleration = acceleration;
}

void Walkable::onUpdate() {
	Movable *movable = object()->component<Movable>();
	if (!movable)
		return;

	movable->setControlAcceleration(m_direction * m_acceleration);
}
