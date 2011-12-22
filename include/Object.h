#ifndef OBJECT_H
#define OBJECT_H

#include <map>
#include <string>

#include "Component.h"
#include "Vector2.h"

class GameEngine;

enum class ObjectType {
	Dynamic,
	Static,
	Kinematic,
	Background,
};

class Object {
public:
	Object(GameEngine *engine);
	Object(GameEngine *engine, const std::string &name);
	virtual ~Object();

	GameEngine * engine() const;
	std::string name() const;
	void setName(const std::string &name);

	ObjectType type() const;
	void setType(ObjectType type);

	Component * component(ComponentType type);
	void addComponent(Component * component);

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
	ObjectType m_type;
};

#endif /* end of include guard: OBJECT_H */
