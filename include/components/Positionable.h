#ifndef POSITIONABLE_H
#define POSITIONABLE_H

#include "Component.h"
#include "Vector2.h"

class Positionable : public Component {
public:
	Positionable(Object *object);
	virtual ~Positionable();

	Vector2 pos() const;
	void setPos(const Vector2 &vec);
	void modifyPos(const Vector2 &vec);

	static const ComponentType componentType;

private:
	Vector2 m_pos;
};

#endif /* end of include guard: POSITIONABLE_H */
