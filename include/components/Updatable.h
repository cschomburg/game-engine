#ifndef UPDATABLE_H
#define UPDATABLE_H

#include "Component.h"

class Updatable : public Component {
public:
	Updatable(ComponentType componentType, Object *object);
	virtual ~Updatable();

	virtual void update() = 0;
};

#endif /* end of include guard: UPDATABLE_H */
