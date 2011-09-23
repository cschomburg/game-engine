#ifndef INPUTSUBSYSTEM_H
#define INPUTSUBSYSTEM_H

#include <SDL/SDL.h>

#include "Subsystem.h"

class Object;

class InputSubsystem : public Subsystem {
public:
	InputSubsystem(GameEngine *engine);
	virtual ~InputSubsystem();

	void update();

	void onEvent(SDL_Event *event);

	void setPlayer(Object *object);
	void updatePlayerDirection();

	void onInputFocus();
	void onInputBlur();

	void onKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);
	void onKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode);

	void onMouseFocus();
	void onMouseBlur();
	void onMouseMove(int mX, int mY, int relX, int relY, bool left, bool right, bool middle);
	void onMouseWheel(bool up, bool down); // Not implemented

	void onLButtonDown(int mX, int mY);
	void onLButtonUp(int mX, int mY);
	void onRButtonDown(int mX, int mY);
	void onRButtonUp(int mX, int mY);
	void onMButtonDown(int mX, int mY);
	void onMButtonUp(int mX, int mY);

	void onJoyAxis(Uint8 which, Uint8 axis, Sint16 value);
	void onJoyButtonDown(Uint8 which, Uint8 button);
	void onJoyButtonUp(Uint8 which, Uint8 button);
	void onJoyHat(Uint8 which, Uint8 hat, Uint8 value);
	void onJoyBall(Uint8 which, Uint8 ball, Sint16 xrel, Sint16 yrel);

	void onMinimize();
	void onRestore();
	void onResize(int w, int h);
	void onExpose();

	void onExit();
	void onUser(Uint8 type, int code, void * data1, void * data2);

private:
	Object *m_player;
};

#endif /* end of include guard: INPUTSUBSYSTEM_H */
