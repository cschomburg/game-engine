#include "Application.h"
#include "Entity.h"

static Vector2 gravitation(0, -1500);

Entity::Entity() {
	m_lastTime = Application::instance()->time();
}

Entity::~Entity() {}

void Entity::onUpdate() {
	Uint32 time = Application::instance()->time();
	float elapsed = float(time - m_lastTime) / 1000;
	m_lastTime = time;

	Vector2 accel = m_acceleration - m_velocity * 4 + gravitation;

	m_velocity += accel * elapsed;
	addPos(m_velocity * elapsed);
}

void Entity::setVelocity(float x, float y) {
	m_velocity.x = x;
	m_velocity.y = y;
}

void Entity::setAcceleration(float x, float y) {
	m_acceleration.x = x;
	m_acceleration.y = y;
}

const Vector2 &Entity::velocity() const {
	return m_velocity;
}

const Vector2 &Entity::acceleration() const {
	return m_acceleration;
}
