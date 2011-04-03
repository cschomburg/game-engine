#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "BaseEngine.h"
#include "Level.h"

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

private:
	Level * m_level;
};

#endif /* end of include guard: GAMEENGINE_H */
