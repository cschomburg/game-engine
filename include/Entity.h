#ifndef ENTITY_H
#define ENTITY_H

#include "Vector.h"

class Entity {
public:
	Entity(float x = 0, float y = 0);

	virtual void onUpdate(float elapsed);

private:
	Vector2 pos;
	Vector2 speed;
}

#endif /* end of include guard: ENTITY_H */
