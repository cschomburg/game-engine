#ifndef OBJECT_H
#define OBJECT_H

#include <map>
#include <string>

#include "Component.h"
#include "Vector2.h"

class GameEngine;

class Object {
public:
	Object(GameEngine *engine);
	Object(GameEngine *engine, const std::string &name);
	virtual ~Object();

	GameEngine * engine() const;
	std::string name() const;
	void setName(const std::string &name);

	Component * component(ComponentType type);
	void addComponent(Component * component);
	void removeComponent(Component * component);
	Component * removeComponent(ComponentType type);

	template<class T> T * component() {
		return static_cast<T *>(component(T::componentType));
	}

	template<class T> T * createComponent() {
		T * component = new T(this);
		m_components[T::componentType] = component;
		return component;
	}

	void onUpdate();

private:
	ComponentMap m_components;
	GameEngine *m_engine;
	std::string m_name;
};

#endif /* end of include guard: OBJECT_H */
