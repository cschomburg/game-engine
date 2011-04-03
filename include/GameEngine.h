#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "BaseEngine.h"
#include "Level.h"
#include "Camera.h"

class GameEngine : public BaseEngine {
public:
	GameEngine();
	virtual ~GameEngine();

	bool loadLevel(const char * file);

private:
	bool onInit();
	void onRender();
	void onExit();
	void onCleanup();

	void onKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);
	void onKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode);

private:
	Level * m_level;
	Camera * m_camera;
};

#endif /* end of include guard: GAMEENGINE_H */
