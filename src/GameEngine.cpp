#include <SDL/SDL_opengl.h>

#include "Application.h"
#include "GameEngine.h"
#include "GameState.h"
#include "states/LevelState.h"
#include "states/WorldManipulateState.h"
#include "Object.h"

#include "SubsystemThread.h"
#include "subsystems/PhysicsSubsystem.h"
#include "subsystems/GraphicsSubsystem.h"
#include "subsystems/LuaSubsystem.h"
#include "subsystems/InputSubsystem.h"
//#include "subsystems/LogicSubsystem.h"

GameEngine::GameEngine() {
	m_player = 0;

	m_physics = std::unique_ptr<PhysicsSubsystem>(new PhysicsSubsystem(this));
	m_graphics = std::unique_ptr<GraphicsSubsystem>(new GraphicsSubsystem(this));
	m_lua = std::unique_ptr<LuaSubsystem>(new LuaSubsystem(this));
	m_input = std::unique_ptr<InputSubsystem>(new InputSubsystem(this));
	//m_logic = new LogicSubsystem(this);
}

GameEngine::~GameEngine() {
}

bool GameEngine::init() {
	m_physics->init();
	m_graphics->init();
	m_lua->init();
	m_input->init();
	//m_logic->init();

	m_lua->push("GameEngine", this, "GameEngine");
	if (!m_lua->loadFile("res/lua/init.lua"))
		return false;

	if (!loadLevel("res/levels/level01.lua"))
		return false;

	pushState(LevelState::instance());
	pushState(WorldManipulateState::instance());

	/*
	SubsystemThread *thread = new SubsystemThread();
	//thread->addSubsystem(m_physics);
	//thread->start();
	m_threads.push_back(thread);

	thread = new SubsystemThread();
	thread->addSubsystem(m_lua);
	thread->addSubsystem(m_logic);
	thread->start();
	m_threads.push_back(thread);

	thread = new SubsystemThread();
	thread->addSubsystem(m_input);
	thread->start();
	m_threads.push_back(thread);
	*/

	return true;
}

void GameEngine::update() {
	m_physics->update();
	m_input->update();
	m_lua->update();
	m_graphics->update();
}

void GameEngine::destroy() {
	for (SubsystemThread *thread : m_threads) {
		thread->stop();
	}
	m_threads.clear();

	m_physics->destroy();
	m_graphics->destroy();
	m_lua->destroy();
	m_input->destroy();
	//m_logic->destroy();

	for (Object *object : m_objects) {
		delete object;
	}
	m_objects.clear();
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

bool GameEngine::loadLevel(std::string file) {
	return m_lua->loadFile(file);
}

void GameEngine::registerObject(Object *object) {
	m_objects.push_back(object);
	objectRegistered(object);
}

void GameEngine::unregisterObject(Object *object) {
	auto it = std::find(m_objects.begin(), m_objects.end(), object);
	if (it == m_objects.end())
		return;
	m_objects.erase(it);
	objectUnregistered(object);
}

Object *GameEngine::player() const {
	return m_player;
}

void GameEngine::setPlayer(Object *player) {
	m_player = player;
	m_graphics->setCamera(player);
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
