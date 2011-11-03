#include <iostream>
#include "components/Collidable.h"
#include "components/Movable.h"
#include "components/Positionable.h"
#include "GameEngine.h"
#include "Object.h"
#include "subsystems/PhysicsSubsystem.h"

const ComponentType Movable::componentType = "Movable";

Movable::Movable(Object *object)
	: Component(componentType, object) {
	object->engine()->physics()->registerComponent(this);
}

Movable::~Movable() {
	object()->engine()->physics()->unregisterComponent(this);
}

bool Movable::update(double dt) {

	Positionable *positionable = object()->component<Positionable>();
	if (!positionable)
		return false;

	Vector2 accel = m_acceleration;
	accel -= m_velocity * 2;
	accel += m_controlAcceleration;
	accel += Vector2(0, -1500); // Gravity, TODO: To Physics engine
	m_velocity += accel * dt;

	Vector2 relPos = m_velocity * dt;
	positionable->modifyPos(relPos);
	return true;
}

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
