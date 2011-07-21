#include <SDL/SDL_opengl.h>

#include "Application.h"
#include "components/all.h"
#include "GameEngine.h"

GameEngine::GameEngine() {
	m_level = 0;
	m_player = 0;
	m_camera = 0;

	//m_lua = new LuaWrapper();
}

GameEngine::~GameEngine() {}

bool GameEngine::loadLevel(const char * file) {
	m_level = new Object();

	Positionable *positionable = new Positionable(m_level);

	Shape *shape = new Shape(m_level);
	shape->setSize(Vector2(2000, 1500));

	Renderable *renderable = new Renderable(m_level);
	renderable->setGradient(Color::fromInt(255, 89, 0), Color::fromInt(180, 20, 0));

	m_level->addComponent(positionable);
	m_level->addComponent(shape);
	m_level->addComponent(renderable);

	m_objects.push_back(m_level);

	return true;
}

bool GameEngine::onInit() {
	if (!loadLevel("res/levels/level01.yaml"))
		return false;

	m_player = new Object();

	Positionable *positionable = new Positionable(m_player);
	positionable->setPos(Vector2(572, 456));

	Shape *shape = new Shape(m_player);
	shape->setSize(Vector2(32, 32));

	Renderable *renderable = new Renderable(m_player);
	renderable->setTexture("res/images/foo.png");

	Walkable *walkable = new Walkable(m_player);
	walkable->setAcceleration(Vector2(1500, 1500));

	m_player->addComponent(positionable);
	m_player->addComponent(new Movable(m_player));
	m_player->addComponent(walkable);
	m_player->addComponent(shape);
	m_player->addComponent(renderable);

	m_objects.push_back(m_player);
	
	m_camera = new Object();

	Tracker *tracker = new Tracker(m_camera);
	tracker->setTracked(m_player);
	m_camera->addComponent(new Positionable(m_camera));
	m_camera->addComponent(tracker);

	m_objects.push_back(m_camera);

	//if (!m_lua->init())
	//	return false;
	//m_lua->push(m_player, "Player");
	//if (!m_lua->loadFile("res/lua/init.lua"))
	//	return false;

	return true;
}

void GameEngine::onUpdate() {
	Uint8 * keystate = SDL_GetKeyState(0);
	float x = keystate[SDLK_RIGHT] - keystate[SDLK_LEFT];
	//float y = keystate[SDLK_UP] - keystate[SDLK_DOWN];

	m_player->component<Walkable>()->setDirection(Vector2(x, 0.0f));

	for (std::vector<Object *>::iterator i = m_objects.begin(); i != m_objects.end(); ++i) {
		(*i)->onUpdate();
	}

	//m_lua->update();
}

void GameEngine::onRender() {
	BaseEngine::onRender();

	Vector2 pos = m_camera->component<Positionable>()->pos();
	glTranslatef(-pos.x, -pos.y, 0);

	for (std::vector<Object *>::iterator i = m_objects.begin(); i != m_objects.end(); ++i) {
		Renderable *renderable = (*i)->component<Renderable>();
		if (renderable)
			renderable->onRender();
	}
}

void GameEngine::onExit() {
	Application::instance()->quit();
}

void GameEngine::onCleanup() {
	BaseEngine::onCleanup();

	//delete m_lua;
	m_level = 0;
	//m_lua = 0;
	m_player = 0;
	m_camera = 0;

	for (std::vector<Object *>::iterator i = m_objects.begin(); i != m_objects.end(); ++i) {
		delete (*i);
	}
	m_objects.clear();
}

void GameEngine::onKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode) {
	if (sym == SDLK_UP) {
		//m_player->setVelocity(m_player->velocity() + Vector2(0, 1000));
	}
}

void GameEngine::onKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode) {
}
