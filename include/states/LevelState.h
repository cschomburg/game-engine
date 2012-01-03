#ifndef LEVELSTATE_H
#define LEVELSTATE_H

#include "GameState.h"

class LevelState : public GameState {
public:
	LevelState();
	virtual ~LevelState();

	virtual bool handle(GameEngine *engine, const SDL_Event &event);

	static LevelState *instance();
};

#endif /* end of include guard: LEVELSTATE_H */
