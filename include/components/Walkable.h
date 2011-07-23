#ifndef WALKABLE_H
#define WALKABLE_H

#include "Component.h"
#include "Vector2.h"

class Walkable : public Component {
public:
	Walkable(Object *object);
	virtual ~Walkable();

	void setDirection(const Vector2 &direction);
	void setAcceleration(const Vector2 &acceleration);
	void jump(const Vector2 &velocity);

	void onUpdate();

	static const ComponentType componentType;

private:
	Vector2 m_direction;
	Vector2 m_lastDirection;
	Vector2 m_acceleration;
};

#endif /* end of include guard: WALKABLE_H */
