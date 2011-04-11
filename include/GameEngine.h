#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "BaseEngine.h"
#include "Level.h"
#include "Camera.h"
#include "Player.h"

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

	Level * level() const;
	bool checkCollision(GameObject * object);
	bool checkCollision(GameObject * object, GameObject * other);

protected:

	void onKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);
	void onKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode);

private:
	Level * m_level;
	Camera * m_camera;
	Player * m_player;
};

#endif /* end of include guard: GAMEENGINE_H */
