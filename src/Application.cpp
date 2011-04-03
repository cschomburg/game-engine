#include <iostream>
#include <fstream>
#include <yaml-cpp/yaml.h>
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>

#include "Application.h"
#include "GameEngine.h"

Application::Application() {
	m_running = false;
	m_display = 0;
}

bool Application::running() const {
	return m_running;
}

void Application::quit() {
	m_running = false;
}

bool Application::execute() {
	if (!onInit())
		return -1;

	m_running = true;

	GameEngine engine;
	engine.execute();

	onCleanup();

	return 0;
}

bool Application::onInit() {

	// load configuration
	
	int width;
	int height;
	bool windowed;

	try {
		std::ifstream fin("properties/config.yaml");
		YAML::Parser parser(fin);
		YAML::Node config;
		parser.GetNextDocument(config);

		config["screen"]["width"] >> width;
		config["screen"]["height"] >> height;
		config["screen"]["windowed"] >> windowed;
	} catch (YAML::Exception &e) {
		std::cout << "Could not load configuration file!" << "\n" << e.what() << "\n";
		return false;
	}

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

	glEnable(GL_TEXTURE_2D);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glViewport(0, 0, width, height);
	glClear(GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-float(width) / 2, float(width)/2, -float(height)/2, float(height)/2, -1.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	glEnable(GL_TEXTURE_2D);

	SDL_EnableKeyRepeat(1, SDL_DEFAULT_REPEAT_INTERVAL / 3);
	return true;
}

void Application::onCleanup() {
	SDL_FreeSurface(m_display);
	m_display = 0;
}
