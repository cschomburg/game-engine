#include <SDL/SDL_opengl.h>

#include "Application.h"
#include "GameEngine.h"
#include "YamlLoader.h"

GameEngine::GameEngine() {
	m_level = 0;
	m_player = 0;
	m_camera = 0;
}

GameEngine::~GameEngine() {}

bool GameEngine::loadLevel(const char * file) {
	m_level = YamlLoader::loadLevel(file);
	if (m_level == 0) {
		return false;
	}
	m_level->onInit();

	return true;
}

bool GameEngine::onInit() {
	if(!loadLevel("res/levels/level01.yaml"))
		return false;

	m_player = new Player();
	m_player->setPos(level()->spawn());

	m_camera = new Camera();
	m_camera->track(m_player);

	return true;
}

void GameEngine::onUpdate() {
	Uint8 * keystate = SDL_GetKeyState(0);
	float x = keystate[SDLK_RIGHT] - keystate[SDLK_LEFT];
	//float y = keystate[SDLK_UP] - keystate[SDLK_DOWN];
	m_player->setMovement(x, 0);

	m_player->onUpdate();
	m_camera->onUpdate();
}

void GameEngine::onRender() {
	BaseEngine::onRender();
	m_camera->onRender();
	m_level->onRender();
	m_player->onRender();
}

void GameEngine::onExit() {
	Application::instance()->quit();
}

void GameEngine::onCleanup() {
	BaseEngine::onCleanup();

	delete m_level;
	delete m_player;
	delete m_camera;
	m_level = 0;
	m_player = 0;
	m_camera = 0;
}

void GameEngine::onKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode) {
	if (sym == SDLK_UP) {
		m_player->setVelocity(m_player->velocity() + Vector2(0, 1000));
	}
}

void GameEngine::onKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode) {
}

Level * GameEngine::level() const {
	return m_level;
}

bool GameEngine::checkCollision(GameObject * object) {
	return checkCollision(object, m_level);
}

bool GameEngine::checkCollision(GameObject * object, GameObject * other) {
	if (!object->collision())
		return false;
	if (other->collides(object))
		return true;

	for (GameObjectsVector::const_iterator i = other->children().begin(); i != other->children().end(); ++i) {
		if ((*i)->collides(object))
			return true;
	}
}
