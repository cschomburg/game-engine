#include "Application.h"
#include "Object.h"

Object::Object() {}

Object::~Object() {
	for (ComponentMap::iterator i = m_components.begin(); i != m_components.end(); ++i) {
		delete i->second;
	}
	m_components.clear();
}

Component * Object::getComponent(ComponentType type) {
	ComponentMap::iterator i = m_components.find(type);
	if (i == m_components.end())
		return 0;
	return i->second;
}

void Object::addComponent(Component * component) {
	if (!component)
		return;

	m_components[component->type()] = component;
}

void Object::removeComponent(Component * component) {
	removeComponent(component->type());
}

Component * Object::removeComponent(ComponentType type) {
	ComponentMap::iterator i = m_components.find(type);
	if (i == m_components.end())
		return 0;
	m_components.erase(i);
	return i->second;
}

void Object::onUpdate() {
	for (ComponentMap::iterator i = m_components.begin(); i != m_components.end(); ++i) {
		i->second->onUpdate();
	}
}
