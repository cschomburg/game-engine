#include <SDL/SDL_opengl.h>

#include "Application.h"
#include "GameEngine.h"
#include "YamlLoader.h"

GameEngine::GameEngine() {
	m_level = 0;
	m_camera = new Camera();
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

	m_camera->setPos(512, 287);

	return true;
}

void GameEngine::onRender() {
	BaseEngine::onRender();
	m_camera->onRender();
	m_level->onRender();
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
			m_camera->addPos(0, 2); break;
		case SDLK_DOWN:
		case SDLK_j:
			m_camera->addPos(0, -2); break;
		case SDLK_LEFT:
		case SDLK_h:
			m_camera->addPos(-2, 0); break;
		case SDLK_RIGHT:
		case SDLK_l:
			m_camera->addPos(2, 0); break;
	}
}

void GameEngine::onKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode) {
}
