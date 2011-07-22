#ifndef COLLIDABLE_H
#define COLLIDABLE_H

#include "Component.h"

class Vector2;

class Collidable : public Component {
public:
	Collidable(Object *object);
	virtual ~Collidable();

	Vector2 collides(Object *other);

	static const ComponentType componentType;
};

#endif /* end of include guard: COLLIDABLE_H */
