#include "Component.h"
#include "components/Movable.h"
#include "components/Collidable.h"
#include "components/Positionable.h"
#include "Object.h"
#include "subsystems/PhysicsSubsystem.h"

PhysicsSubsystem::PhysicsSubsystem(GameEngine *engine)
	: Subsystem(engine) {}

PhysicsSubsystem::~PhysicsSubsystem() {}

void PhysicsSubsystem::registerComponent(Movable *component) {
	m_movables.insert(component);
}

void PhysicsSubsystem::registerComponent(Collidable *component) {
	m_collidables.insert(component);
}

void PhysicsSubsystem::unregisterComponent(Movable *component) {
	m_movables.erase(component);
}

void PhysicsSubsystem::unregisterComponent(Collidable *component) {
	m_collidables.erase(component);
}

void PhysicsSubsystem::update() {
	// TODO: position events
	handleMovements();
	handleCollisions();
}

void PhysicsSubsystem::handleMovements() {
	for (auto &movable : m_movables) {
		if (!movable->update())
			continue;

		Collidable *collidable = movable->object()->component<Collidable>();
		if (collidable) {
			m_collisionUpdates.push_back(collidable);
		}
	}
}

void PhysicsSubsystem::handleCollisions() {

	while (!m_collisionUpdates.empty()) {
		Collidable *collidable = m_collisionUpdates.front();
		m_collisionUpdates.pop_front();
		Vector2 collVectorTotal;
		Vector2 collVector;

		for (auto &other: m_collidables) {
			if (collidable->collides(other->object(), &collVector)) {
				collVectorTotal += collVector;
			}
		}

		collidable->setLastCollisionVector(collVectorTotal);
		collidable->object()->component<Positionable>()->modifyPos(collVectorTotal);
		// TODO:: Spawn collision events
		//collVec.normalize();
		//m_velocity -= collVec * m_velocity.dot(collVec);
	}
}
