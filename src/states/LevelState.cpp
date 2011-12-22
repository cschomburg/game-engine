#include <Box2D/Box2D.h>

#include "Application.h"
#include "GameEngine.h"
#include "Object.h"
#include "components/Body.h"
#include "states/LevelState.h"

LevelState sInstance;

LevelState::LevelState()
	: GameState("LevelState") {}

LevelState::~LevelState() {}

bool LevelState::handle(const SDL_Event &event) {
	if (event.type == SDL_QUIT) {
		Application::instance()->quit();
		return false;
	}

	GameEngine *engine = Application::instance()->engine();

	Object *player = engine->player();
	if (player) {
		Body *body = player->component<Body>();

		// Jumping
		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_UP) {
			body->body()->ApplyForceToCenter(b2Vec2(0, 50));
			return true;
		}

		// Left/Right
		if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
			SDLKey key = event.key.keysym.sym;
			if (key == SDLK_LEFT || key == SDLK_RIGHT) {
				Uint8 *keystate = SDL_GetKeyState(0);
				int x = keystate[SDLK_RIGHT] - keystate[SDLK_LEFT];
				body->body()->ApplyForce(b2Vec2(10*x, 20), body->body()->GetWorldPoint(b2Vec2(0.04*x, 0)));
				return true;
			}
		}
	}

	return false;
}

LevelState *LevelState::instance() {
	return &sInstance;
}
