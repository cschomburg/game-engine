#include <iostream>

#include "GameEngine.h"
#include "ResourceManager.h"

#include "subsystems/Profiler.h"
#include "subsystems/PhysicsSubsystem.h"
#include "subsystems/GraphicsSubsystem.h"
#include "subsystems/LuaSubsystem.h"
#include "subsystems/InputSubsystem.h"

GameEngine *sInstance = 0;

GameEngine::GameEngine() {
	sInstance = this;

	m_running = false;
	m_display = 0;

	m_manager = std::unique_ptr<ResourceManager>(new ResourceManager());
	m_profiler = std::unique_ptr<Profiler>(new Profiler(this));

	m_physics = std::unique_ptr<PhysicsSubsystem>(new PhysicsSubsystem(this));
	m_graphics = std::unique_ptr<GraphicsSubsystem>(new GraphicsSubsystem(this));
	m_lua = std::unique_ptr<LuaSubsystem>(new LuaSubsystem(this));
	m_input = std::unique_ptr<InputSubsystem>(new InputSubsystem(this));
}

GameEngine::~GameEngine() {
	sInstance = 0;
}

GameEngine *GameEngine::instance() {
	return sInstance;
}

bool GameEngine::isRunning() const {
	return m_running;
}

void GameEngine::quit() {
	m_running = false;
}

bool GameEngine::execute() {
	if (!init()) {
		std::cout << "Could not initialize game engine!" << std::endl;
		return false;
	}

	m_running = true;
	while (m_running) {
		update();
	}

	destroy();
	return true;
}

bool GameEngine::init() {
	// Load configuration
	m_displayWidth = 1024;
	m_displayHeight = 576;
	m_windowed = true;

	// Initialize SDL
	Uint32 flags = SDL_OPENGL;
	if (!m_windowed)
		flags |= SDL_FULLSCREEN;

	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		printf("SDL: Unable to initialize: %s\n", SDL_GetError());
		return false;
	}
	//SDL_GL_SetAttribute(SDL_GL_SWAP_CONTROL, 1);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	if ((m_display = SDL_SetVideoMode(m_displayWidth, m_displayHeight, 32, flags)) == 0) {
		printf("SDL: SetVideoMode failed: %s\n", SDL_GetError());
		return false;
	}
	//SDL_EnableKeyRepeat(1, SDL_DEFAULT_REPEAT_INTERVAL / 3);
	
	// Initialize subsystems	
	m_profiler->init();
	m_physics->init();
	m_graphics->init();
	m_lua->init();
	m_input->init();

	// Load level
	if (!m_lua->loadFile("res/lua/main.lua"))
		return false;

	return true;
}

void GameEngine::update() {
	m_profiler->start("Update");

	m_profiler->start("Physics");
	m_physics->update();
	m_profiler->stop("Physics");

	m_profiler->start("Input");
	m_input->update();
	m_profiler->stop("Input");

	m_profiler->start("Lua");
	m_lua->update();
	m_profiler->stop("Lua");

	m_profiler->start("Graphics");
	m_graphics->update();
	m_profiler->stop("Graphics");

	m_profiler->stop("Update");
}

void GameEngine::destroy() {
	m_profiler->report(std::cout);

	m_profiler->destroy();
	m_physics->destroy();
	m_graphics->destroy();
	m_lua->destroy();
	m_input->destroy();

	SDL_FreeSurface(m_display);
	m_display = 0;
}

int GameEngine::time() const {
	return SDL_GetTicks();
}

bool GameEngine::windowed() const {
	return m_windowed;
}

int GameEngine::displayWidth() const {
	return m_displayWidth;
}

int GameEngine::displayHeight() const {
	return m_displayHeight;
}

ResourceManager *GameEngine::manager() const {
	return m_manager.get();
}

Profiler *GameEngine::profiler() const {
	return m_profiler.get();
}


PhysicsSubsystem *GameEngine::physics() const {
	return m_physics.get();
}

GraphicsSubsystem *GameEngine::graphics() const {
	return m_graphics.get();
}

LuaSubsystem *GameEngine::lua() const {
	return m_lua.get();
}

InputSubsystem *GameEngine::input() const {
	return m_input.get();
}
