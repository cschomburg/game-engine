#ifndef COMPONENT_H
#define COMPONENT_H

#include <map>
#include <string>
#include <iostream>

typedef std::string ComponentType;

class Object;

class Component {
public:
	Component(ComponentType type, Object *object);
	virtual ~Component();

	ComponentType type() const;
	Object * object() const;

private:
	ComponentType m_type;
	Object *m_object;
};

typedef std::map<ComponentType, Component *> ComponentMap;

std::ostream& operator<<(std::ostream &o, const Component *a);

#endif /* end of include guard: COMPONENT_H */
