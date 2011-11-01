#include <algorithm>
#include <map>

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
	std::vector<Collision> collisions;

	// Check collisions between every collidable object
	while (!m_collisionUpdates.empty()) {
		Collidable *collidable = m_collisionUpdates.front();
		m_collisionUpdates.pop_front();
		Vector2 collVectorTotal;
		Vector2 collVector;

		for (auto &other: m_collidables) {
			if (collidable->collides(other->object(), &collVector)) {
				collVectorTotal += collVector;

				// Already a collision detected between these objects?
				auto it = std::find_if(collisions.begin(), collisions.end(), [=](Collision &collision) {
					return (collision.b == collidable && collision.a == other);
				});
				if (it == collisions.end()) {
					collisions.push_back(Collision{collidable, other, collVector});
				}
			}
		}

		// Reset position
		collidable->setLastCollisionVector(collVectorTotal);
		collidable->object()->component<Positionable>()->modifyPos(collVectorTotal);
	}

	// Handle detected collisions
	while (!collisions.empty()) {
		Collision collision = collisions.back();
		collisions.pop_back();

		Movable *movableA = collision.a->object()->component<Movable>();
		Movable *movableB = collision.b->object()->component<Movable>();

		// Elastic collision
		if (movableA && movableB) {
			collision.vector.normalize();
			float massA = collision.a->weight();
			float massB = collision.b->weight();
			float velA = movableA->velocity().dot(collision.vector);
			float velB = movableB->velocity().dot(collision.vector);

			float velAnew = (velA*(massA-massB) + 2*massB*velB) / (massA+massB);
			float velBnew = (velB*(massB-massA) + 2*massA*velA) / (massB+massA);
			Vector2 velADiff = collision.vector * (velAnew-velA);
			Vector2 velBDiff = collision.vector * (velBnew-velB);

			movableA->modifyVelocity(velADiff);
			movableB->modifyVelocity(velBDiff);
		}

		// TODO:: Spawn collision events
	}
}
