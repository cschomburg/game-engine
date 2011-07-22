#include "components/Collidable.h"
#include "components/Shape.h"
#include "Object.h"
#include "Rect.h"
#include "Vector2.h"

const ComponentType Collidable::componentType = "Collidable";

Collidable::Collidable(Object *object)
	: Component(componentType, object) {}

Collidable::~Collidable() {}

Vector2 Collidable::collides(Object *other) {
	if (other == object() || !other->component<Collidable>())
		return Vector2();

	Shape *shape = object()->component<Shape>();
	Shape *otherShape = other->component<Shape>();
	if (!shape || !otherShape)
		return Vector2();

	Rect rect = shape->worldBoundingBox();
	Rect otherRect = otherShape->worldBoundingBox();

	if (!rect.intersects(otherRect))
		return Vector2();

	return Vector2(1, 1);
}
