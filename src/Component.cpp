#include "Component.h"

Component::Component(const std::string &type, const std::string &objectID) {
	m_type = type;
	m_objectID = objectID;
}

Component::~Component() {}

std::string Component::type() const {
	return m_type;
}

std::string Component::objectID() const {
	return m_objectID;
}
