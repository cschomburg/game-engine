#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <vector>

#include "BaseEngine.h"
#include "Object.h"
//#include "lua/LuaWrapper.h"

class GameEngine : public BaseEngine {
public:
	GameEngine();
	virtual ~GameEngine();

	bool loadLevel(const char * file);

	bool onInit();
	void onUpdate();
	void onRender();
	void onExit();
	void onCleanup();

protected:

	void onKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);
	void onKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode);

private:
	Object * m_level;
//	LuaWrapper * m_lua;
	Object * m_player;
	Object * m_camera;
	std::vector<Object *> m_objects;
};

#endif /* end of include guard: GAMEENGINE_H */
