#include "Application.h"
#include "GameEngine.h"
#include "Object.h"

Object::Object(GameEngine *engine) {
	m_engine = engine;
	m_type = ObjectType::Dynamic;
}

Object::Object(GameEngine *engine, const std::string &name) {
	m_engine = engine;
	m_name = name;
}

Object::~Object() {
	for (auto &it : m_components) {
		delete it.second;
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

ObjectType Object::type() const {
	return m_type;
}

void Object::setType(ObjectType type) {
	m_type = type;
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
