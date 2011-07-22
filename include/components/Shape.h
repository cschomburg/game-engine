#ifndef SHAPE_H
#define SHAPE_H

#include <vector>

#include "Component.h"
#include "Polygon.h"
#include "Rect.h"
#include "Vector2.h"

class Rect;

class Shape : public Component {
public:
	Shape(Object *object);
	virtual ~Shape();

	Polygon shape() const;
	void setShape(const Polygon &shape);

	Rect boundingBox() const;

	static const ComponentType componentType;

private:
	Polygon m_shape;
	Rect m_boundingBox;
};

#endif /* end of include guard: SHAPE_H */
