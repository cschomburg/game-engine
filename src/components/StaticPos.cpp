#include "components/StaticPos.h"

StaticPos::StaticPos(const std::string &objectID)
	: Component("StaticPos", objectID), IPositionable() {
	m_pos = Vector2();
	m_angle = 0;
}

StaticPos::~StaticPos() {}

Vector2 StaticPos::pos() const {
	return m_pos;
}

void StaticPos::setPos(const Vector2 &pos) {
	m_pos = pos;
}

float StaticPos::angle() const {
	return m_angle;
}

void StaticPos::setAngle(float angle) {
	m_angle = angle;
}
