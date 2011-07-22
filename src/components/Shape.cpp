#include "components/Positionable.h"
#include "components/Shape.h"
#include "Object.h"
#include "Rect.h"

const ComponentType Shape::componentType = "Shape";

Shape::Shape(Object *object)
	: Component(componentType, object) {}

Shape::~Shape() {}

Vector2 Shape::size() const {
	return m_size;
}

void Shape::setSize(const Vector2 &size) {
	m_size = size;
}

Rect Shape::boundingBox() const {
	return Rect(Vector2(), m_size);
}

Rect Shape::worldBoundingBox() const {
	Positionable *positionable = object()->component<Positionable>();

	if (!positionable)
		return boundingBox();

	return Rect(positionable->pos(), m_size);
}
