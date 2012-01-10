#include "LuaCall.h"
#include "subsystems/InputSubsystem.h"
#include "subsystems/LuaSubsystem.h"

InputSubsystem::InputSubsystem(GameEngine *engine)
	: Subsystem(engine) {
}

InputSubsystem::~InputSubsystem() {}

void InputSubsystem::update() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		handleEvent(&event);
	}
}

std::string InputSubsystem::keyToString(SDLKey sym) {
	// Letters and symbols
	if (sym >= 32 && sym <= 127) {
		return std::string(1, static_cast<char>(sym));
	}

	auto it = keyMap.find(sym);
	if (it == keyMap.end()) {
		return "Unknown";
	}
	return it->second;
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
		LuaCall::Ptr call = engine()->lua()->startGlobalCall("onKeyDown");
		if (call) {
			call->push(keyToString(event->key.keysym.sym));
			//mods = modToString(event->key.keysym.mod);
			call->execute();
		}
		break;
	}
	case SDL_KEYUP: {
		LuaCall::Ptr call = engine()->lua()->startGlobalCall("onKeyUp");
		if (call) {
			call->push(keyToString(event->key.keysym.sym));
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
		LuaCall::Ptr call = engine()->lua()->startGlobalCall("onMouseButtonDown");
		if (call) {
			call->push(event->button.button);
			call->push(event->button.x);
			call->push(event->button.y);
			call->execute();
		}
		break;
	}
	case SDL_MOUSEBUTTONUP: {
		LuaCall::Ptr call = engine()->lua()->startGlobalCall("onMouseButtonUp");
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
	LuaCall::Ptr call = engine()->lua()->startGlobalCall(event);
	if (call) {
		call->execute();
	}
}

std::map<SDLKey, std::string> InputSubsystem::keyMap{
	{ SDLK_UNKNOWN, "Unknown" },
	{ SDLK_FIRST, "First" },
	{ SDLK_BACKSPACE, "Backspace" },
	{ SDLK_TAB, "Tab" },
	{ SDLK_CLEAR, "Clear" },
	{ SDLK_RETURN, "Return" },
	{ SDLK_PAUSE, "Pause" },
	{ SDLK_ESCAPE, "Escape" },
	// Letters and symbols can be converted directly
	{ SDLK_DELETE, "Delete", },
	// International keyboard syms
	// Numeric keypad
	{ SDLK_KP0, "KP0" },
	{ SDLK_KP1, "KP1" },
	{ SDLK_KP2, "KP2" },
	{ SDLK_KP3, "KP3" },
	{ SDLK_KP4, "KP4" },
	{ SDLK_KP5, "KP5" },
	{ SDLK_KP6, "KP6" },
	{ SDLK_KP7, "KP7" },
	{ SDLK_KP8, "KP8" },
	{ SDLK_KP9, "KP9" },
	{ SDLK_KP_PERIOD, "KP." },
	{ SDLK_KP_DIVIDE, "KP/" },
	{ SDLK_KP_MULTIPLY, "KP*" },
	{ SDLK_KP_MINUS, "KP-" },
	{ SDLK_KP_PLUS, "KP+" },
	{ SDLK_KP_ENTER, "KP_Enter"},
	{ SDLK_KP_EQUALS, "KP=" },
	// Arrows + Home/End pad
	{ SDLK_UP, "Up" },
	{ SDLK_DOWN, "Down" },
	{ SDLK_RIGHT, "Right" },
	{ SDLK_LEFT, "Left" },
	{ SDLK_INSERT, "Insert" },
	{ SDLK_HOME, "Home" },
	{ SDLK_END, "End" },
	{ SDLK_PAGEUP, "PageUp" },
	{ SDLK_PAGEDOWN, "PageDown" },
	// Function keys
	{ SDLK_F1, "F1" },
	{ SDLK_F2, "F2" },
	{ SDLK_F3, "F3" },
	{ SDLK_F4, "F4" },
	{ SDLK_F5, "F5" },
	{ SDLK_F6, "F6" },
	{ SDLK_F7, "F7" },
	{ SDLK_F8, "F8" },
	{ SDLK_F9, "F9" },
	{ SDLK_F10, "F10" },
	{ SDLK_F11, "F11" },
	{ SDLK_F12, "F12" },
	{ SDLK_F13, "F13" },
	{ SDLK_F14, "F14" },
	{ SDLK_F15, "F15" },
	// Key state modifier keys
	{ SDLK_NUMLOCK, "Numlock" },
	{ SDLK_CAPSLOCK, "Capslock" },
	{ SDLK_SCROLLOCK, "ScrollLock" },
	{ SDLK_RSHIFT, "RShift" },
	{ SDLK_LSHIFT, "LShift" },
	{ SDLK_RCTRL, "RCtrl" },
	{ SDLK_LCTRL, "LCtrl" },
	{ SDLK_RALT, "RAlt" },
	{ SDLK_LALT, "LAlt" },
	{ SDLK_RMETA, "RMeta" },
	{ SDLK_LMETA, "LMeta" },
	{ SDLK_LSUPER, "LSuper" },
	{ SDLK_RSUPER, "RSuper" },
	{ SDLK_MODE, "Mode" },
	{ SDLK_COMPOSE, "Compose" },
	// Miscellaneous function keys
	{ SDLK_HELP, "Help" },
	{ SDLK_PRINT, "Print" },
	{ SDLK_SYSREQ, "SysReq" },
	{ SDLK_BREAK, "Break" },
	{ SDLK_MENU, "Menu" },
	{ SDLK_POWER, "Power" },
	{ SDLK_EURO, "Euro" },
	{ SDLK_UNDO, "Undo" },
};

std::map<SDLMod, std::string> InputSubsystem::modMap{
	{ KMOD_LSHIFT, "LShift" },
	{ KMOD_RSHIFT, "RShift" },
	{ KMOD_LCTRL, "LCtrl" },
	{ KMOD_RCTRL, "RCtrl" },
	{ KMOD_LALT, "LAlt" },
	{ KMOD_RALT, "RAlt" },
	{ KMOD_LMETA, "LMeta" },
	{ KMOD_RMETA, "RMeta" },
	{ KMOD_NUM, "NumLock" },
	{ KMOD_CAPS, "CapsLock" },
	{ KMOD_MODE, "Mode" },
	{ KMOD_RESERVED, "Reserved" },
};

