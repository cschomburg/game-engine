#include "GameState.h"

GameState::GameState(const std::string &name) {
	m_name = name;
	m_active = false;
}

GameState::~GameState() {}

std::string GameState::name() const {
	return m_name;
}

bool GameState::active() const {
	return m_active;
}

void GameState::enter(GameEngine *engine) {
	m_active = true;
}

void GameState::leave(GameEngine *engine) {
	m_active = false;
}

bool GameState::handle(GameEngine *engine, const SDL_Event &event) {
	return false;
}
