#include <iostream>

#include "GameEngine.h"
#include "GameState.h"
#include "ResourceManager.h"

#include "states/LevelState.h"
#include "states/WorldManipulateState.h"
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
	m_physics = std::unique_ptr<PhysicsSubsystem>(new PhysicsSubsystem(this));
	m_graphics = std::unique_ptr<GraphicsSubsystem>(new GraphicsSubsystem(this));
	m_lua = std::unique_ptr<LuaSubsystem>(new LuaSubsystem(this));
	m_input = std::unique_ptr<InputSubsystem>(new InputSubsystem(this));
	//m_logic = new LogicSubsystem(this);
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
	m_physics->init();
	m_graphics->init();
	m_lua->init();
	m_input->init();
	//m_logic->init();

	// Load level
	if (!m_lua->loadFile("res/lua/init.lua"))
		return false;

	if (!m_lua->loadFile("res/levels/level01.lua"))
		return false;

	pushState(LevelState::instance());
	pushState(WorldManipulateState::instance());

	return true;
}

void GameEngine::update() {
	m_physics->update();
	m_input->update();
	m_lua->update();
	m_graphics->update();
}

void GameEngine::destroy() {
	m_physics->destroy();
	m_graphics->destroy();
	m_lua->destroy();
	m_input->destroy();
	//m_logic->destroy();

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

GameState *GameEngine::state() const {
	return m_states.back();
}

const std::vector<GameState *> GameEngine::states() const {
	return m_states;
}

void GameEngine::pushState(GameState *state) {
	m_states.push_back(state);
	state->enter(this);
}

void GameEngine::popState() {
	GameState *state = m_states.back();
	m_states.pop_back();
	if (state)
		state->leave(this);
}

ResourceManager *GameEngine::manager() const {
	return m_manager.get();
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

/*
LogicSubsystem *GameEngine::logic() const {
	return m_logic;
}*/
