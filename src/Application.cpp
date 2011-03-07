#include <iostream>
#include <fstream>
#include <yaml-cpp/yaml.h>

#include "Application.h"
#include "BaseEngine.h"

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

	BaseEngine engine;
	engine.setDisplay(m_display);
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

	Uint32 flags = SDL_HWSURFACE | SDL_DOUBLEBUF;
	if (!windowed)
		flags |= SDL_FULLSCREEN;

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		printf("SDL: Init failed!\n");
		return false;
	}
	if ((m_display = SDL_SetVideoMode(width, height, 32, flags)) == 0) {
		printf("SDL: SetVideoMode failed!\n");
		return false;
	}

	SDL_EnableKeyRepeat(1, SDL_DEFAULT_REPEAT_INTERVAL / 3);
	return true;
}

void Application::onCleanup() {
	SDL_FreeSurface(m_display);
	m_display = 0;
}
