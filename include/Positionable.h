#ifndef POSITIONABLE_H
#define POSITIONABLE_H

#include "Vector2.h"

class Positionable {
public:
	Positionable(float x = 0, float y = 0, float w = 0, float h = 0);

	const Vector2 &pos() const;
	void setPos(float x, float y);
	void setPos(const Vector2 &pos);
	void addPos(float x, float y);
	void addPos(const Vector2 &pos);

	const Vector2 &size() const;
	void setSize(float w, float y);
	void setSize(const Vector2 &size);

private:
	Vector2 m_pos;
	Vector2 m_size;
};

#endif /* end of include guard: POSITIONABLE_H */
