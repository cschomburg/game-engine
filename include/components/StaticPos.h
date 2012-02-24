#ifndef STATICPOSITIONABLE_H
#define STATICPOSITIONABLE_H

#include <memory>
#include <string>

#include "Component.h"
#include "Vector2.h"
#include "interfaces/IPositionable.h"

class StaticPos : public Component, public IPositionable {
public:
	typedef std::shared_ptr<StaticPos> Ptr;

	StaticPos();
	virtual ~StaticPos();

	Vector2 pos() const;
	void setPos(const Vector2 &pos);

	float angle() const;
	void setAngle(float angle);

private:
	Vector2 m_pos;
	float m_angle;

};

#endif /* end of include guard: STATICPOSITIONABLE_H */
