#include "components/Shape.h"

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
