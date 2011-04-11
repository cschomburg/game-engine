#ifndef ENTITY_H
#define ENTITY_H

#include "GameObject.h"

class Entity : public GameObject {
public:
	Entity();
	virtual ~Entity();

	virtual void onUpdate();

	void setVelocity(float x, float y);
	void setAcceleration(float x, float y);
	void setAcceleration(const Vector2 &acceleration);

	const Vector2 &velocity() const;
	const Vector2 &acceleration() const;

private:
	Uint32 m_lastTime;

	Vector2 m_velocity;
	Vector2 m_acceleration;
};

#endif /* end of include guard: ENTITY_H */
