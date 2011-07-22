#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <vector>

#include "BaseEngine.h"
#include "Object.h"
#include "lua/LuaWrapper.h"

class Vector2;

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

	bool checkCollision(Object *object, Vector2 *collVector);

protected:

	void onKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);
	void onKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode);

private:
	LuaWrapper * m_lua;
	Object * m_level;
	Object * m_player;
	Object * m_camera;
	std::vector<Object *> m_objects;
};

#endif /* end of include guard: GAMEENGINE_H */
