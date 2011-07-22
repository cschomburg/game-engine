#include "components/Shape.h"

const ComponentType Shape::componentType = "Shape";

Shape::Shape(Object *object)
	: Component(componentType, object) {}

Shape::~Shape() {}

Polygon Shape::shape() const {
	return m_shape;
}

void Shape::setShape(const Polygon &shape) {
	m_shape = shape;
	m_boundingBox = shape.boundingBox();
}

Rect Shape::boundingBox() const {
	return m_boundingBox;
}
