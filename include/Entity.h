#ifndef ENTITY_H
#define ENTITY_H

#include "GameObject.h"

class Entity : public GameObject {
public:
	Entity();
	virtual ~Entity();

	virtual void onUpdate();

	const Vector2 &velocity() const;
	void setVelocity(const Vector2 &acceleration);
	const Vector2 &acceleration() const;
	void setAcceleration(const Vector2 &acceleration);

private:
	Uint32 m_lastTime;

	Vector2 m_velocity;
	Vector2 m_acceleration;
};

#endif /* end of include guard: ENTITY_H */
