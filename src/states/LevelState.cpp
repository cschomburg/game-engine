#include "Application.h"
#include "GameEngine.h"
#include "Object.h"
#include "components/Walkable.h"
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
		Walkable *walkable = player->component<Walkable>();

		// Jumping
		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_UP) {
			if (walkable)
				walkable->jump(Vector2(0, 1500));
			return true;
		}

		// Left/Right
		if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
			SDLKey key = event.key.keysym.sym;
			if (key == SDLK_LEFT || key == SDLK_RIGHT) {
				Uint8 *keystate = SDL_GetKeyState(0);
				int x = keystate[SDLK_RIGHT] - keystate[SDLK_LEFT];
				if (walkable)
					walkable->setDirection(Vector2(x, 0));
				return true;
			}
		}
	}

	return false;
}

LevelState *LevelState::instance() {
	return &sInstance;
}
