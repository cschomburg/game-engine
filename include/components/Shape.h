#ifndef SHAPE_H
#define SHAPE_H

#include <vector>
#include <Box2D/Box2D.h>

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

	b2PolygonShape shape() const;
	void setShape(const b2PolygonShape &shape);

	b2AABB boundingBox() const;

	static const ComponentType componentType;

private:
	b2PolygonShape m_shape;
	b2AABB m_boundingBox;
};

#endif /* end of include guard: SHAPE_H */
