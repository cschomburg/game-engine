#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <string>
#include <vector>

#include "Subsystem.h"

class GameState;
class Object;
class PhysicsSubsystem;
class GraphicsSubsystem;
class LuaSubsystem;
class InputSubsystem;
class LogicSubsystem;

class SubsystemThread;

class GameEngine {
public:
	GameEngine();
	virtual ~GameEngine();

	bool init();
	void update();
	void destroy();

	GameState *state() const;
	const std::vector<GameState *> states() const;
	void pushState(GameState *state);
	void popState();

	bool loadLevel(std::string file);
	Object *level() const;
	Object *player() const;

	PhysicsSubsystem *physics() const;
	GraphicsSubsystem *graphics() const;
	LuaSubsystem *lua() const;
	InputSubsystem *input() const;
	LogicSubsystem *logic() const;

private:
	PhysicsSubsystem *m_physics;
	GraphicsSubsystem *m_graphics;
	LuaSubsystem *m_lua;
	InputSubsystem *m_input;
	LogicSubsystem *m_logic;
	std::vector<SubsystemThread *> m_threads;

	std::vector<GameState *> m_states;

	Object *m_level;
	Object *m_player;
	std::vector<Object *> m_objects;
};

#endif /* end of include guard: GAMEENGINE_H */
