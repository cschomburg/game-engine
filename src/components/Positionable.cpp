#include "Application.h"
#include "components/Positionable.h"
#include "components/Movable.h"

const ComponentType Positionable::componentType = "Positionable";

Positionable::Positionable(Object *object)
	: Component(componentType, object) {}

Positionable::~Positionable() {}

Vector2 Positionable::pos() const {
	return m_pos;
}

void Positionable::setPos(const Vector2 &pos) {
	Vector2 oldPos = m_pos;
	m_pos = pos;

	Vector2 collVec;
	if (Application::instance()->engine()->checkCollision(object(), &collVec)) {
		m_pos += collVec;

		Movable *movable = object()->component<Movable>();
		if (movable) {
			collVec.normalize();
			movable->modifyVelocity((collVec * -1) * (movable->velocity().dot(collVec)));
		}
	}
}

void Positionable::modifyPos(const Vector2 &pos) {
	setPos(m_pos + pos);
}
