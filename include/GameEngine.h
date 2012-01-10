#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include <memory>
#include <string>
#include <vector>
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>

class ResourceManager;
class PhysicsSubsystem;
class GraphicsSubsystem;
class LuaSubsystem;
class InputSubsystem;
class UISubsystem;
class Profiler;

class GameEngine {
public:
	GameEngine();
	virtual ~GameEngine();

	static GameEngine *instance();

	bool isRunning() const;
	void quit();
	bool execute();
	int time() const;

	bool windowed() const;
	int displayWidth() const;
	int displayHeight() const;

	ResourceManager *manager() const;
	Profiler *profiler() const;

	PhysicsSubsystem *physics() const;
	GraphicsSubsystem *graphics() const;
	LuaSubsystem *lua() const;
	InputSubsystem *input() const;
	UISubsystem *ui() const;


private:
	bool init();
	void update();
	void destroy();

private:
	static GameEngine * s_instance;
	bool m_running;

	bool m_windowed;
	int m_displayWidth;
	int m_displayHeight;
	SDL_Surface *m_display;

	std::unique_ptr<ResourceManager> m_manager;
	std::unique_ptr<Profiler> m_profiler;

	std::unique_ptr<PhysicsSubsystem> m_physics;
	std::unique_ptr<GraphicsSubsystem> m_graphics;
	std::unique_ptr<LuaSubsystem> m_lua;
	std::unique_ptr<InputSubsystem> m_input;
	std::unique_ptr<UISubsystem> m_ui;
};

#endif /* end of include guard: GAMEENGINE_H */
