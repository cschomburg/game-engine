#ifndef IPOSITIONABLE_H
#define IPOSITIONABLE_H

#include <memory>
#include "Vector2.h"

class IPositionable {
public:
	typedef std::shared_ptr<IPositionable> Ptr;
	typedef std::weak_ptr<IPositionable> WeakPtr;

	IPositionable() {};
	virtual ~IPositionable() {};

	virtual Vector2 pos() const = 0;
	virtual void setPos(const Vector2 &pos) = 0;

	virtual float angle() const = 0;
	virtual void setAngle(float angle) = 0;
};

#endif /* end of include guard: IPOSITIONABLE_H */
