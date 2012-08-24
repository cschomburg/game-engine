#include "LuaCall.h"
#include "subsystems/InputSubsystem.h"
#include "subsystems/LuaSubsystem.h"

InputSubsystem::InputSubsystem(GameEngine *engine)
	: Subsystem(engine) {
}

InputSubsystem::~InputSubsystem() {}

bool InputSubsystem::init() {
	SDL_EnableUNICODE(1);
	return true;
}

void InputSubsystem::update() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		handleEvent(&event);
	}
}

std::vector<std::string> InputSubsystem::modToString(SDLMod mod) {
	std::vector<std::string> mods;
	for (auto pair : modMap) {
		if (pair.first > mod)
			break;
		if (mod & pair.first) {
			mods.push_back(pair.second);
		}
	}
	return mods;
}

void InputSubsystem::handleEvent(SDL_Event *event) {
	switch(event->type) {
	case SDL_ACTIVEEVENT: {
		switch(event->active.state) {
		case SDL_APPMOUSEFOCUS: {
			if (event->active.gain) {
				simpleCall("onMouseFocusGain");
			} else {
				simpleCall("onMouseFocusLost");
			}
			break;
		}

		case SDL_APPINPUTFOCUS: {
			if (event->active.gain) {
				simpleCall("onAppInputFocusGain");
			} else {
				simpleCall("onAppInputFocusLost");
			}
			break;
		}

		case SDL_APPACTIVE: {
			if (event->active.gain) {
				simpleCall("onRestore");
			} else {
				simpleCall("onMinimize");
			}
			break;
		}
		}
		break;
	}

	case SDL_KEYDOWN: {
		LuaCall::Ptr call = engine()->lua()->startEventCall("onKeyDown");
		if (call) {
			call->push(std::string(SDL_GetKeyName(event->key.keysym.sym)));
			//mods = modToString(event->key.keysym.mod);
			if ((event->key.keysym.unicode & 0xFF80) == 0) {
				char ch = event->key.keysym.unicode & 0x7F;
				call->push(std::string(1, ch));
			} else {
				call->push(std::string("???"));
			}
			call->execute();
		}
		break;
	}
	case SDL_KEYUP: {
		LuaCall::Ptr call = engine()->lua()->startEventCall("onKeyUp");
		if (call) {
			call->push(std::string(SDL_GetKeyName(event->key.keysym.sym)));
			//mods = modToString(event->key.keysym.mod);
			call->execute();
		}
		break;
	}

	case SDL_MOUSEMOTION: {
		simpleCall("onMouseMove");
		/*onMouseMove(event->motion.x, event->motion.y, event->motion.xrel, event->motion.yrel,
					(event->motion.state & SDL_BUTTON(SDL_BUTTON_LEFT)) != 0,
					(event->motion.state & SDL_BUTTON(SDL_BUTTON_RIGHT)) != 0,
					(event->motion.state & SDL_BUTTON(SDL_BUTTON_MIDDLE)) != 0
		);*/
		break;
	}
	case SDL_MOUSEBUTTONDOWN: {
		LuaCall::Ptr call = engine()->lua()->startEventCall("onMouseButtonDown");
		if (call) {
			call->push(event->button.button);
			call->push(event->button.x);
			call->push(event->button.y);
			call->execute();
		}
		break;
	}
	case SDL_MOUSEBUTTONUP: {
		LuaCall::Ptr call = engine()->lua()->startEventCall("onMouseButtonUp");
		if (call) {
			call->push(event->button.button);
			call->push(event->button.x);
			call->push(event->button.y);
			call->execute();
		}
		break;
	}

	/*
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
	*/

	case SDL_QUIT: {
		simpleCall("onQuit");
		engine()->quit();
		break;
	}
	case SDL_SYSWMEVENT: {
		// Ignore
		break;
	 }
	case SDL_VIDEORESIZE: {
		simpleCall("onResize");
		//onResize(event->resize.w, event->resize.h);
		break;
	}
	case SDL_VIDEOEXPOSE: {
		simpleCall("onExpose");
		break;
	}
	
	default: {
		//onUser(event->user.type, event->user.code, event->user.data1, event->user.data2);
		break;
	}
	}
}

void InputSubsystem::simpleCall(const std::string &event) {
	LuaCall::Ptr call = engine()->lua()->startEventCall(event);
	if (call) {
		call->execute();
	}
}

std::map<int, std::string> InputSubsystem::modMap{
	{ KMOD_SHIFT, "shift" },
	{ KMOD_LSHIFT, "lshift" },
	{ KMOD_RSHIFT, "rshift" },
	{ KMOD_CTRL, "ctrl" },
	{ KMOD_LCTRL, "lctrl" },
	{ KMOD_RCTRL, "rctrl" },
	{ KMOD_ALT, "alt" },
	{ KMOD_LALT, "lalt" },
	{ KMOD_RALT, "ralt" },
	{ KMOD_META, "meta" },
	{ KMOD_LMETA, "lmeta" },
	{ KMOD_RMETA, "rmeta" },
	{ KMOD_NUM, "numlock" },
	{ KMOD_CAPS, "capslock" },
	{ KMOD_MODE, "Mode" },
	{ KMOD_RESERVED, "reserved" },
};

