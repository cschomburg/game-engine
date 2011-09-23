#include "components/Positionable.h"
#include "components/Tracker.h"
#include "components/Walkable.h"
#include "Object.h"
#include "GameEngine.h"
#include "subsystems/LogicSubsystem.h"

const ComponentType Tracker::componentType = "Tracker";

Tracker::Tracker(Object *object)
	: Updatable(componentType, object) {
	m_tracked = 0;
	object->engine()->logic()->registerComponent(this);
}

Tracker::~Tracker() {
	object()->engine()->logic()->unregisterComponent(this);
}

void Tracker::setTracked(Object *object) {
	m_tracked = object;
}

void Tracker::update() {
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
