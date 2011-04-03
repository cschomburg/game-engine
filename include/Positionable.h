#ifndef ENTITY_H
#define ENTITY_H

#include "Vector2.h"

class Positionable {
public:
	Positionable(float x = 0, float y = 0);

	const Vector2 &pos() const;
	void setPos(float x, float y);
	void setPos(const Vector2 &pos);
	void addPos(float x, float y);
	void addPos(const Vector2 &pos);

private:
	Vector2 m_pos;
};

#endif /* end of include guard: ENTITY_H */
