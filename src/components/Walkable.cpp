#include "components/Collidable.h"
#include "components/Movable.h"
#include "components/Walkable.h"
#include "Object.h"
#include "GameEngine.h"
#include "subsystems/LogicSubsystem.h"

const ComponentType Walkable::componentType = "Walkable";

Walkable::Walkable(Object *object)
	: Updatable(componentType, object) {
	object->engine()->logic()->registerComponent(this);
}

Walkable::~Walkable() {
	object()->engine()->logic()->unregisterComponent(this);
}

void Walkable::setDirection(const Vector2 &direction) {
	m_direction = direction;
	m_direction.normalize();
}

void Walkable::setAcceleration(const Vector2 &acceleration) {
	m_acceleration = acceleration;
}

void Walkable::jump(const Vector2 &velocity) {
	Collidable *collidable = object()->component<Collidable>();
	Movable *movable = object()->component<Movable>();
	if (!collidable || !movable)
		return;

	Vector2 collVec = collidable->lastCollisionVector();
	if (collVec.isZero())
		return;

	collVec.normalize();
	movable->modifyVelocity(collVec * velocity.magnitude());
}

void Walkable::update() {
	Movable *movable = object()->component<Movable>();
	if (!movable)
		return;

	movable->setControlAcceleration(m_direction * m_acceleration);
}
