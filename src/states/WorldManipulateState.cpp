#include "states/WorldManipulateState.h"
#include "subsystems/PhysicsSubsystem.h"

static WorldManipulateState sInstance;

WorldManipulateState::WorldManipulateState()
	: GameState("WorldManipulateState") {}

WorldManipulateState::~WorldManipulateState() {}

bool WorldManipulateState::handle(GameEngine *engine, const SDL_Event &event) {

	PhysicsSubsystem *physics = engine->physics();

	// Timefactor
	if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_w) {
		physics->setTimeFactor(physics->timeFactor() / 0.9);
		return true;
	}
	if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_s) {
		physics->setTimeFactor(physics->timeFactor() * 0.9);
		return true;
	}

	// Freeze
	if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_e) {
		if (physics->timeFactor() == 0.0f) {
			physics->setTimeFactor(m_timeFactor);
		} else {
			m_timeFactor = physics->timeFactor();
			physics->setTimeFactor(0.0f);
		}
		return true;
	}

	return false;
}

WorldManipulateState *WorldManipulateState::instance() {
	return &sInstance;
}
