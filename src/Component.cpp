#include <iostream>
#include "Component.h"

Component::Component(const std::string &type) {
	m_type = type;
}

Component::~Component() {}

std::string Component::type() const {
	return m_type;
}

void Component::setObjectID(const std::string &objectID) {
	m_objectID = objectID;
}

std::string Component::objectID() const {
	return m_objectID;
}
