#ifndef POSITIONABLE_H
#define POSITIONABLE_H

#include <memory>
#include <string>

#include "Vector2.h"

class Positionable {
public:
	typedef std::shared_ptr<Positionable> Ptr;

	Positionable();
	virtual ~Positionable();

	virtual Vector2 pos() const;
	virtual void setPos(const Vector2 &pos);

	virtual float angle() const;
	virtual void setAngle(float angle);

	std::shared_ptr<Positionable> anchor() const;
	void setAnchor(std::shared_ptr<Positionable> positionable);
	Vector2 worldPos() const;


private:
	Vector2 m_pos;
	float m_angle;
	std::shared_ptr<Positionable> m_anchor;

};

#endif /* end of include guard: POSITIONABLE_H */
