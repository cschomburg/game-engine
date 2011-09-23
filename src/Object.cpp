#include "Application.h"
#include "GameEngine.h"
#include "Object.h"

Object::Object(GameEngine *engine) {
	m_engine = engine;
}

Object::Object(GameEngine *engine, const std::string &name) {
	m_engine = engine;
	m_name = name;
}

Object::~Object() {
	for (ComponentMap::iterator i = m_components.begin(); i != m_components.end(); ++i) {
		delete i->second;
	}
	m_components.clear();
}

GameEngine * Object::engine() const {
	return m_engine;
}

std::string Object::name() const {
	return m_name;
}

void Object::setName(const std::string &name) {
	m_name = name;
}

Component * Object::component(ComponentType type) {
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
