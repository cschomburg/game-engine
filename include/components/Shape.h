#ifndef SHAPE_H
#define SHAPE_H

#include <vector>

#include "Component.h"
#include "Rect.h"
#include "Vector2.h"
#include "Convex.h"

class Rect;
class Convex;

class Shape : public Component {
public:
	Shape(Object *object);
	virtual ~Shape();

	Convex shape() const;
	void setShape(const Convex &shape);

	Rect boundingBox() const;

	static const ComponentType componentType;

private:
	Convex m_shape;
	Rect m_boundingBox;
};

#endif /* end of include guard: SHAPE_H */
