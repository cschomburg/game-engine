#ifndef WORLDMANIPULATESTATE_H
#define WORLDMANIPULATESTATE_H

#include "GameState.h"

class WorldManipulateState : public GameState {
public:
	WorldManipulateState();
	virtual ~WorldManipulateState();

	virtual bool handle(const SDL_Event &event);

	static WorldManipulateState *instance();

private:
	float m_timeFactor;
};

#endif /* end of include guard: WORLDMANIPULATESTATE_H */
