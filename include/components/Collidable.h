#ifndef COLLIDABLE_H
#define COLLIDABLE_H

#include "Component.h"
#include "Vector2.h"

class Collidable : public Component {
public:
	Collidable(Object *object);
	virtual ~Collidable();

	bool collides(Object *other, Vector2 *collVector = 0);

	Vector2 lastCollisionVector() const;
	void setLastCollisionVector(const Vector2 &collVector);

	static const ComponentType componentType;

private:
	Vector2 m_lastCollVector;
};

#endif /* end of include guard: COLLIDABLE_H */
