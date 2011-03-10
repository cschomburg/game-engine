#include "GameEngine.h"

GameEngine::GameEngine() {
	m_level = 0;
	m_texture = 0;
}

GameEngine::~GameEngine() {}

bool GameEngine::loadLevel(const char * file) {
	if ((m_level = Level::fromFile(file)) == 0) {
		return false;
	}

	return true;
}

bool GameEngine::onInit() {
	if(!loadLevel("res/levels/level01.yaml"))
		return false;
	if ((m_texture = Texture::fromFile("res/images/island.png")) == 0)
		return false;

	return true;
}

void GameEngine::onRender() {
	SDL_Surface * disp = display();
	m_level->onRender(disp);
	m_texture->draw(disp, 50, 50);
}

void GameEngine::onExit() {
	quit();
}

void GameEngine::onCleanup() {
	BaseEngine::onCleanup();

	delete m_texture;
	m_texture = 0;
}
