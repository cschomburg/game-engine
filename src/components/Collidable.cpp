#include "components/Collidable.h"
#include "components/Positionable.h"
#include "components/Shape.h"
#include "Object.h"
#include "Rect.h"

const ComponentType Collidable::componentType = "Collidable";

Collidable::Collidable(Object *object)
	: Component(componentType, object) {}

Collidable::~Collidable() {}

bool Collidable::collides(Object *other, Vector2 *collVector) {
	if (other == object() || !other->component<Collidable>())
		return false;

	Shape *shape = object()->component<Shape>();
	Shape *otherShape = other->component<Shape>();
	if (!shape || !otherShape)
		return false;

	Positionable *pos = object()->component<Positionable>();
	Positionable *otherPos = other->component<Positionable>();
	if (!pos || !otherPos)
		return false;

	Rect rect = shape->boundingBox();
	Rect otherRect = otherShape->boundingBox();
	rect.translate(pos->pos());
	otherRect.translate(otherPos->pos());


	// Test bounding box collision
	if (!rect.intersects(otherRect))
		return false;

	// At last, convex convexgon collision
	Convex convex = shape->shape();
	Convex otherConvex = otherShape->shape();
	convex.translate(pos->pos());
	otherConvex.translate(otherPos->pos());

	return convex.intersects(otherConvex, collVector);
}

Vector2 Collidable::lastCollisionVector() const {
	return m_lastCollVector;
}

void Collidable::setLastCollisionVector(const Vector2 &collVector) {
	m_lastCollVector = collVector;
}
