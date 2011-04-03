#include <SDL/SDL.h>

#include "Environment.h"

Environment Environment::gInstance;

Environment * Environment::instance()
{
	return &g_instance;
}

Environment::Environment() {}
Environment::~Environment() {}

bool Environment::init(Game *game, int screenWidth, int screenHeight, bool fullscreen, const char *windowTitle)
{
	m_game = game;

	// Platform interface
	m_interface = new GlInterface(game, screenWidth, screenHeight, fullscreen, windowTitle);

	// timing
	m_updateCount = 0;
	m_lastUpdate = SDL_GetTicks();

}


