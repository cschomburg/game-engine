#ifndef COLLIDABLE_H
#define COLLIDABLE_H

#include "Component.h"

class Vector2;

class Collidable : public Component {
public:
	Collidable(Object *object);
	virtual ~Collidable();

	bool collides(Object *other, Vector2 *collVector = 0);

	static const ComponentType componentType;
};

#endif /* end of include guard: COLLIDABLE_H */
