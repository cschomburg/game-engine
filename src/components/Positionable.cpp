#include "Application.h"
#include "components/Positionable.h"

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

	Vector2 collVec = Application::instance()->engine()->checkCollision(object());
	if (!collVec.isZero()) {
		m_pos = oldPos;
	}
}

void Positionable::modifyPos(const Vector2 &pos) {
	setPos(m_pos + pos);
}
