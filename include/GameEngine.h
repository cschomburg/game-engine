#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <string>
#include <vector>

#include "Subsystem.h"

class Object;
class PhysicsSubsystem;
class GraphicsSubsystem;
class LuaSubsystem;
class InputSubsystem;
class LogicSubsystem;

class GameEngine {
public:
	GameEngine();
	virtual ~GameEngine();

	bool init();
	void update();
	void destroy();

	bool loadLevel(std::string file);
	Object * level() const;

	PhysicsSubsystem * physics() const;
	GraphicsSubsystem * graphics() const;
	LuaSubsystem * lua() const;
	InputSubsystem * input() const;
	LogicSubsystem * logic() const;

private:
	PhysicsSubsystem *m_physics;
	GraphicsSubsystem *m_graphics;
	LuaSubsystem *m_lua;
	InputSubsystem *m_input;
	LogicSubsystem *m_logic;

	Object *m_level;
	std::vector<Object *> m_objects;
};

#endif /* end of include guard: GAMEENGINE_H */
