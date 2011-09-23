#include <iostream>
#include <fstream>
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>

#include "Application.h"

Application::Application() {
	m_running = false;
	m_display = 0;
	m_fps = 0;

	m_engine = 0;
	m_manager = new ResourceManager();
}

Application * Application::instance() {
	if (App)
		return App;
	App = new Application();
	return App;
}

bool Application::running() const {
	return m_running;
}

void Application::quit() {
	m_running = false;
}

bool Application::execute() {
	if (!init())
		return false;

	m_engine = new GameEngine();
	if (!m_engine->init()) {
		std::cout << "Could not initialize game engine!" << std::endl;
		return false;
	}

	m_running = true;
	while (m_running) {
		m_engine->update();
	}

	m_engine->destroy();
	delete m_engine;
	m_engine = 0;

	destroy();

	return true;
}

bool Application::init() {

	// load configuration
	
	int width = 1024;
	int height = 576;
	bool windowed = true;

	// initialize SDL

	Uint32 flags = SDL_OPENGL;
	if (!windowed)
		flags |= SDL_FULLSCREEN;

	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		printf("SDL: Unable to initialize: %s\n", SDL_GetError());
		return false;
	}
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	if ((m_display = SDL_SetVideoMode(width, height, 32, flags)) == 0) {
		printf("SDL: SetVideoMode failed: %s\n", SDL_GetError());
		return false;
	}

	m_windowed = windowed;
	m_displayWidth = width;
	m_displayHeight = height;

	//SDL_EnableKeyRepeat(1, SDL_DEFAULT_REPEAT_INTERVAL / 3);

	return true;
}

void Application::destroy() {
	SDL_FreeSurface(m_display);
	m_display = 0;
}

int Application::time() const {
	return SDL_GetTicks();
}

bool Application::windowed() const {
	return m_windowed;
}

int Application::displayWidth() const {
	return m_displayWidth;
}

int Application::displayHeight() const {
	return m_displayHeight;
}

GameEngine * Application::engine() const {
	return m_engine;
}

ResourceManager * Application::manager() const {
	return m_manager;
}
