#include "components/Shape.h"

const ComponentType Shape::componentType = "Shape";

Shape::Shape(Object *object)
	: Component(componentType, object) {}

Shape::~Shape() {}

b2PolygonShape Shape::shape() const {
	return m_shape;
}

void Shape::setShape(const b2PolygonShape &shape) {
	m_shape = shape;

	b2AABB box;
	m_boundingBox = shape.ComputeAABB(&box, b2Transform(), 0);
}

b2AABB Shape::boundingBox() const {
	return m_boundingBox;
}
