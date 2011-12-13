#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <string>
#include <SDL/SDL.h>

class GameEngine;

class GameState {
public:
	GameState(const std::string &name);
	virtual ~GameState();

	std::string name() const;
	bool active() const;

	virtual void enter(GameEngine *engine);
	virtual void leave(GameEngine *engine);

	virtual bool handle(const SDL_Event &event);

private:
	std::string m_name;
	bool m_active;
};

#endif /* end of include guard: GAMESTATE_H */
