#include "GameEngine.h"
#include "Subsystem.h"

Subsystem::Subsystem(GameEngine *engine) {
	m_engine = engine;
}

Subsystem::~Subsystem() {}

GameEngine * Subsystem::engine() const {
	return m_engine;
}

bool Subsystem::init() {
	return true;
}

void Subsystem::update() {}

void Subsystem::destroy() {}
