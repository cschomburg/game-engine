#include <iostream>
#include "Component.h"

Component::Component(const std::string &type, const std::string &objectID) {
	m_type = type;
	m_objectID = objectID;

	std::cout << "[C] " << m_objectID << "::" << m_type << std::endl;
}

Component::~Component() {
	std::cout << "[D] " << m_objectID << "::" << m_type << std::endl;
}

std::string Component::type() const {
	return m_type;
}

std::string Component::objectID() const {
	return m_objectID;
}
