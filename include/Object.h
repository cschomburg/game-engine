#ifndef OBJECT_H
#define OBJECT_H

#include <map>

#include "Component.h"
#include "Vector2.h"

class Object {
public:
	Object();
	virtual ~Object();

	Component * getComponent(ComponentType type);
	void addComponent(Component * component);
	void removeComponent(Component * component);
	Component * removeComponent(ComponentType type);

	template<class T> T * component() {
		return static_cast<T *>(getComponent(T::componentType));
	}

	void onUpdate();

private:
	ComponentMap m_components;
};

#endif /* end of include guard: OBJECT_H */
