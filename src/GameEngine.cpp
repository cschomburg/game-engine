#include <SDL/SDL_opengl.h>

#include "GameEngine.h"
#include "YamlLoader.h"

GameEngine::GameEngine() {
	m_level = 0;
}

GameEngine::~GameEngine() {}

bool GameEngine::loadLevel(const char * file) {
	m_level = YamlLoader::loadLevel(file);
	if (m_level == 0) {
		return false;
	}

	return true;
}

bool GameEngine::onInit() {
	if(!loadLevel("res/levels/level01.yaml"))
		return false;

	return true;
}

void GameEngine::onRender() {
	BaseEngine::onRender();
	m_level->onRender();
}

void GameEngine::onExit() {
	quit();
}

void GameEngine::onCleanup() {
	BaseEngine::onCleanup();

	delete m_level;
	m_level = 0;
}
