#include "components/Updatable.h"
#include "subsystems/LogicSubsystem.h"

LogicSubsystem::LogicSubsystem(GameEngine *engine)
	: Subsystem(engine) {}

LogicSubsystem::~LogicSubsystem() {}

void LogicSubsystem::update() {
	for (Updatable *updatable : m_updatables) {
		updatable->update();
	}
}

void LogicSubsystem::registerComponent(Updatable *component) {
	m_updatables.insert(component);
}

void LogicSubsystem::unregisterComponent(Updatable *component) {
	m_updatables.erase(component);
}
