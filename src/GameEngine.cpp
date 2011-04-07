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
	m_player->setPos(572, 1000);

	m_camera = new Camera();
	m_camera->setPos(m_player->pos());

	return true;
}

void GameEngine::onUpdate() {
	m_player->onUpdate();
	m_camera->setPos(m_player->pos());
}

void GameEngine::onRender() {
	BaseEngine::onRender();
	m_camera->onRender();
	m_level->onRender();
	m_player->onRender();
}

void GameEngine::onExit() {
	App->quit();
}

void GameEngine::onCleanup() {
	BaseEngine::onCleanup();

	delete m_level;
	m_level = 0;
}

void GameEngine::onKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode) {
	switch(sym) {
		case SDLK_UP:
		case SDLK_k:
			m_player->setAcceleration(0, 500); break;
		case SDLK_DOWN:
		case SDLK_j:
			m_player->setAcceleration(0, -500); break;
		case SDLK_LEFT:
		case SDLK_h:
			m_player->setAcceleration(-500, 0); break;
		case SDLK_RIGHT:
		case SDLK_l:
			m_player->setAcceleration(500, 0); break;
	}
}

void GameEngine::onKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode) {
	switch(sym) {
		case SDLK_UP:
		case SDLK_k:
		case SDLK_LEFT:
		case SDLK_h:
		case SDLK_DOWN:
		case SDLK_j:
		case SDLK_RIGHT:
		case SDLK_l:
			m_player->setAcceleration(0, 0); break;
	}
}
