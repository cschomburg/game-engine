#include "components/Positionable.h"
#include "components/Tracker.h"
#include "components/Walkable.h"
#include "Object.h"

const ComponentType Tracker::componentType = "Tracker";

Tracker::Tracker(Object *object)
	: Component(componentType, object) {
	m_tracked = 0;
}

Tracker::~Tracker() {}

void Tracker::setTracked(Object *object) {
	m_tracked = object;
}

void Tracker::onUpdate() {
	if (!m_tracked)
		return;

	Positionable *positionable = object()->component<Positionable>();
	Positionable *otherPositionable = m_tracked->component<Positionable>();

	if (!positionable || !otherPositionable)
		return;

	Walkable *walkable = object()->component<Walkable>();
	if (walkable) {
		walkable->setDirection(otherPositionable->pos() - positionable->pos());
	} else {
		positionable->setPos(otherPositionable->pos());
	}
}
