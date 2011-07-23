#include "components/Collidable.h"
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

	Vector2 accel = m_acceleration;
	accel -= m_velocity * 2;
	accel += m_controlAcceleration;
	accel += Vector2(0, -1500); // Gravity
	m_velocity += accel * elapsed;

	Vector2 relPos = m_velocity * elapsed;
	if (relPos.magnitude() < 0.001)
		return;

	positionable->modifyPos(relPos);

	Collidable *collidable = object()->component<Collidable>();
	if (!collidable)
		return;

	Vector2 collVec;
	if (Application::instance()->engine()->checkCollision(object(), &collVec)) {
		collidable->setLastCollisionVector(collVec);
		positionable->modifyPos(collVec);

		collVec.normalize();
		m_velocity -= collVec * m_velocity.dot(collVec);
	} else {
		collidable->setLastCollisionVector(Vector2());
	}
}
