#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <memory>
#include <string>
#include <vector>
#include <boost/signals2.hpp>

#include "Subsystem.h"

class GameState;
class Object;
class PhysicsSubsystem;
class GraphicsSubsystem;
class LuaSubsystem;
class InputSubsystem;
//class LogicSubsystem;

class SubsystemThread;

typedef boost::signals2::signal<void (Object *)> ObjectSignal;

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
	void registerObject(Object *object);
	void unregisterObject(Object *object);
	Object *player() const;
	void setPlayer(Object *object);

	PhysicsSubsystem *physics() const;
	GraphicsSubsystem *graphics() const;
	LuaSubsystem *lua() const;
	InputSubsystem *input() const;
	//LogicSubsystem *logic() const;

public:
	ObjectSignal objectRegistered;
	ObjectSignal objectUnregistered;


private:
	std::unique_ptr<PhysicsSubsystem> m_physics;
	std::unique_ptr<GraphicsSubsystem> m_graphics;
	std::unique_ptr<LuaSubsystem> m_lua;
	std::unique_ptr<InputSubsystem> m_input;
	//LogicSubsystem *m_logic;
	std::vector<SubsystemThread *> m_threads;

	std::vector<GameState *> m_states;

	Object *m_player;
	std::vector<Object *> m_objects;
};

#endif /* end of include guard: GAMEENGINE_H */
