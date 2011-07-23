#ifndef MOVABLE_H
#define MOVABLE_H

#include "Application.h"
#include "Component.h"
#include "Vector2.h"

class Movable : public Component {
public:
	Movable(Object *object);
	virtual ~Movable();

	Vector2 velocity() const;
	void setVelocity(const Vector2 &velocity);
	void modifyVelocity(const Vector2 &velocity);

	Vector2 acceleration() const;
	void setAcceleration(const Vector2 &acceleration);
	void modifyAcceleration(const Vector2 &acceleration);

	Vector2 controlAcceleration() const;
	void setControlAcceleration(const Vector2 &acceleration);

	void onUpdate();

	static const ComponentType componentType;

private:
	Uint32 m_lastTime;
	Vector2 m_velocity;
	Vector2 m_acceleration;
	Vector2 m_direction;
	Vector2 m_controlAcceleration;
};

#endif /* end of include guard: MOVABLE_H */
