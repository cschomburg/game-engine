#include "Application.h"
#include "Object.h"
#include "components/Walkable.h"
#include "subsystems/InputSubsystem.h"

InputSubsystem::InputSubsystem(GameEngine *engine)
	: Subsystem(engine) {
	m_player = 0;
}

InputSubsystem::~InputSubsystem() {}

void InputSubsystem::update() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		onEvent(&event);
	}
	SDL_Delay(1);
}

void InputSubsystem::onEvent(SDL_Event *event) {
	switch(event->type) {
	case SDL_ACTIVEEVENT: {
		switch(event->active.state) {
		case SDL_APPMOUSEFOCUS: {
			if (event->active.gain) {
				onMouseFocus();
			} else {
				onMouseBlur();
			}
			break;
		}

		case SDL_APPINPUTFOCUS: {
			if (event->active.gain) {
				onInputFocus();
			} else {
				onInputBlur();
			}
			break;
		}

		case SDL_APPACTIVE: {
			if (event->active.gain) {
				onRestore();
			} else {
				onMinimize();
			}
			break;
		}
		}
		break;
	}

	case SDL_KEYDOWN: {
		onKeyDown(event->key.keysym.sym, event->key.keysym.mod, event->key.keysym.unicode);
		break;
	}
	case SDL_KEYUP: {
		onKeyUp(event->key.keysym.sym, event->key.keysym.mod, event->key.keysym.unicode);
		break;
	}

	case SDL_MOUSEMOTION: {
		onMouseMove(event->motion.x, event->motion.y, event->motion.xrel, event->motion.yrel,
					(event->motion.state & SDL_BUTTON(SDL_BUTTON_LEFT)) != 0,
					(event->motion.state & SDL_BUTTON(SDL_BUTTON_RIGHT)) != 0,
					(event->motion.state & SDL_BUTTON(SDL_BUTTON_MIDDLE)) != 0
		);
		break;
	}
	case SDL_MOUSEBUTTONDOWN: {
		switch(event->button.button) {
		case SDL_BUTTON_LEFT: {
			onLButtonDown(event->button.x, event->button.y);
			break;
		}
		case SDL_BUTTON_RIGHT: {
			onRButtonDown(event->button.x, event->button.y);
			break;
		}
		case SDL_BUTTON_MIDDLE: {
			onMButtonDown(event->button.x, event->button.y);
			break;
		}
		}
		break;
	}
	case SDL_MOUSEBUTTONUP: {
		switch(event->button.button) {
		case SDL_BUTTON_LEFT: {
			onLButtonUp(event->button.x, event->button.y);
			break;
		}
		case SDL_BUTTON_RIGHT: {
			onRButtonUp(event->button.x, event->button.y);
			break;
		}
		case SDL_BUTTON_MIDDLE: {
			onMButtonUp(event->button.x, event->button.y);
			break;
		}
		}
		break;
	}
	
	case SDL_JOYAXISMOTION: {
		onJoyAxis(event->jaxis.which, event->jaxis.axis, event->jaxis.value);
		break;
	}
	case SDL_JOYBALLMOTION: {
		onJoyBall(event->jball.which, event->jball.ball, event->jball.xrel, event->jball.yrel);
		break;
	}
	case SDL_JOYBUTTONDOWN: {
		onJoyButtonDown(event->jbutton.which, event->jbutton.button);
		break;
	}
	case SDL_JOYBUTTONUP: {
		onJoyButtonUp(event->jbutton.which, event->jbutton.button);
		break;
	}

	case SDL_QUIT: {
		onExit();
		break;
	}
	case SDL_SYSWMEVENT: {
		// Ignore
		break;
	 }
	case SDL_VIDEORESIZE: {
		onResize(event->resize.w, event->resize.h);
		break;
	}
	case SDL_VIDEOEXPOSE: {
		onExpose();
		break;
	}
	
	default: {
		onUser(event->user.type, event->user.code, event->user.data1, event->user.data2);
		break;
	}
	}
}

void InputSubsystem::setPlayer(Object *object) {
	m_player = object;
}

void InputSubsystem::updatePlayerDirection() {
	if (!m_player)
		return;

	Uint8 * keystate = SDL_GetKeyState(0);
	float x = keystate[SDLK_RIGHT] - keystate[SDLK_LEFT];
	m_player->component<Walkable>()->setDirection(Vector2(x, 0));
}

void InputSubsystem::onInputFocus() {}
void InputSubsystem::onInputBlur() {}

void InputSubsystem::onKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode) {
	if (sym == SDLK_UP && m_player) {
		Walkable *walkable = m_player->component<Walkable>();
		if (walkable)
			walkable->jump(Vector2(0, 1500));
	}

	if (sym == SDLK_LEFT || sym == SDLK_RIGHT) {
		updatePlayerDirection();
	}
}
void InputSubsystem::onKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode) {

	if (sym == SDLK_LEFT || sym == SDLK_RIGHT) {
		updatePlayerDirection();
	}
}

void InputSubsystem::onMouseFocus() {}
void InputSubsystem::onMouseBlur() {}
void InputSubsystem::onMouseMove(int mX, int mY, int relX, int relY, bool left, bool right, bool middle) {}
void InputSubsystem::onMouseWheel(bool up, bool down) {}

void InputSubsystem::onLButtonDown(int mX, int mY) {}
void InputSubsystem::onLButtonUp(int mX, int mY) {}
void InputSubsystem::onRButtonDown(int mX, int mY) {}
void InputSubsystem::onRButtonUp(int mX, int mY) {}
void InputSubsystem::onMButtonDown(int mX, int mY) {}
void InputSubsystem::onMButtonUp(int mX, int mY) {}

void InputSubsystem::onJoyAxis(Uint8 which, Uint8 axis, Sint16 value) {}
void InputSubsystem::onJoyButtonDown(Uint8 which, Uint8 button) {}
void InputSubsystem::onJoyButtonUp(Uint8 which, Uint8 button) {}
void InputSubsystem::onJoyHat(Uint8 which, Uint8 hat, Uint8 value) {}
void InputSubsystem::onJoyBall(Uint8 which, Uint8 ball, Sint16 xrel, Sint16 yrel) {}

void InputSubsystem::onMinimize() {}
void InputSubsystem::onRestore() {}
void InputSubsystem::onResize(int w, int h) {}
void InputSubsystem::onExpose() {}

void InputSubsystem::onExit() {
	Application::instance()->quit();
}

void InputSubsystem::onUser(Uint8 type, int code, void * data1, void * data2) {}

