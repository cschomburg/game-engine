#include "components/Movable.h"
#include "components/Positionable.h"

const ComponentType Movable::componentType = "Movable";

Movable::Movable(Object *object)
	: Component(componentType, object) {
	m_lastTime = Application::instance()->time();
}

Movable::~Movable() {}

Vector2 Movable::velocity() const {
	return m_velocity;
}

void Movable::setVelocity(const Vector2 &velocity) {
	m_velocity = velocity;
}

void Movable::modifyVelocity(const Vector2 &velocity) {
	m_velocity += velocity;
}

Vector2 Movable::acceleration() const {
	return m_acceleration;
}

void Movable::setAcceleration(const Vector2 &acceleration) {
	m_acceleration = acceleration;
}

void Movable::modifyAcceleration(const Vector2 &acceleration) {
	m_acceleration += acceleration;
}

Vector2 Movable::controlAcceleration() const {
	return m_controlAcceleration;
}

void Movable::setControlAcceleration(const Vector2 &acceleration) {
	m_controlAcceleration = acceleration;
}

void Movable::onUpdate() {
	Uint32 time = Application::instance()->time();
	float elapsed = float(time - m_lastTime) / 1000;
	m_lastTime = time;

	Positionable *positionable = object()->component<Positionable>();
	if (!positionable)
		return;

	Vector2 accel = m_acceleration; // + Application::instance()->engine()->level()->gravitation();
	accel -= m_velocity * 2;
	accel += m_controlAcceleration;
	m_velocity += accel * elapsed;

	if (m_velocity.magnitude() < 1)
		return;

	positionable->modifyPos(m_velocity * elapsed);
}
