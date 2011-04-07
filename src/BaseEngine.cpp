#include <SDL/SDL_opengl.h>

#include "BaseEngine.h"

BaseEngine::BaseEngine() {
	m_running = false;
	m_fps = 0;
}

BaseEngine::~BaseEngine() {}

bool BaseEngine::onInit() {
	return true;
}

void BaseEngine::onUpdate() {}

void BaseEngine::onRender() {
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void BaseEngine::onCleanup() {}

void BaseEngine::onEvent(SDL_Event * event) {
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

void BaseEngine::onInputFocus() {}
void BaseEngine::onInputBlur() {}

void BaseEngine::onKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode) {}
void BaseEngine::onKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode) {}

void BaseEngine::onMouseFocus() {}
void BaseEngine::onMouseBlur() {}
void BaseEngine::onMouseMove(int mX, int mY, int relX, int relY, bool left, bool right, bool middle) {}
void BaseEngine::onMouseWheel(bool up, bool down) {}

void BaseEngine::onLButtonDown(int mX, int mY) {}
void BaseEngine::onLButtonUp(int mX, int mY) {}
void BaseEngine::onRButtonDown(int mX, int mY) {}
void BaseEngine::onRButtonUp(int mX, int mY) {}
void BaseEngine::onMButtonDown(int mX, int mY) {}
void BaseEngine::onMButtonUp(int mX, int mY) {}

void BaseEngine::onJoyAxis(Uint8 which, Uint8 axis, Sint16 value) {}
void BaseEngine::onJoyButtonDown(Uint8 which, Uint8 button) {}
void BaseEngine::onJoyButtonUp(Uint8 which, Uint8 button) {}
void BaseEngine::onJoyHat(Uint8 which, Uint8 hat, Uint8 value) {}
void BaseEngine::onJoyBall(Uint8 which, Uint8 ball, Sint16 xrel, Sint16 yrel) {}

void BaseEngine::onMinimize() {}
void BaseEngine::onRestore() {}
void BaseEngine::onResize(int w, int h) {}
void BaseEngine::onExpose() {}

void BaseEngine::onExit() {}
void BaseEngine::onUser(Uint8 type, int code, void * data1, void * data2) {}
