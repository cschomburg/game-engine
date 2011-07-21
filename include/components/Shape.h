#ifndef SHAPE_H
#define SHAPE_H

#include "Component.h"
#include "Vector2.h"

class Shape : public Component {
public:
	Shape(Object *object);
	virtual ~Shape();

	Vector2 size() const;
	void setSize(const Vector2 &size);

	static const ComponentType componentType;

private:
	Vector2 m_size;
};

#endif /* end of include guard: SHAPE_H */
