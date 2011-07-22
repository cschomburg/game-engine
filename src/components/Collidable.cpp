#include "components/Collidable.h"
#include "components/Positionable.h"
#include "components/Shape.h"
#include "Object.h"
#include "Rect.h"
#include "Vector2.h"

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

	// At last, polygon collision
	Polygon poly = shape->shape();
	Polygon otherPoly = otherShape->shape();
	poly.translate(pos->pos());
	otherPoly.translate(otherPos->pos());

	return poly.intersects(otherPoly, collVector);
}
