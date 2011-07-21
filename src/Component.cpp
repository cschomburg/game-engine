#include "Component.h"
#include "Object.h"

Component::Component(ComponentType type, Object *object) {
	m_type = type;
	m_object = object;
}

Component::~Component() {}

ComponentType Component::type() const {
	return m_type;
}

Object * Component::object() const {
	return m_object;
}

void Component::onUpdate() {}

std::ostream& operator<<(std::ostream &o, const Component *a) {
	return o << a->type();
}
