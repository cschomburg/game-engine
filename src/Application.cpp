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
	if (!onInit())
		return -1;

	m_running = true;
	SDL_Event event;

	Uint32 lastTime = SDL_GetTicks();
	int frameCount = 0;

	while (m_running) {
		while (SDL_PollEvent(&event)) {
			m_engine->onEvent(&event);
		}

		frameCount++;
		if ((SDL_GetTicks() - lastTime) >= 1000) {
			m_fps = frameCount;
			frameCount = 0;
			lastTime = SDL_GetTicks();
			//printf("%d\n", m_fps);
		}

		m_engine->onUpdate();
		m_engine->onRender();
		SDL_GL_SwapBuffers();
	}

	m_engine->onCleanup();

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

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-float(width) / 2, float(width)/2, -float(height)/2, float(height)/2, -1.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	//glEnable(GL_DEPTH_TEST);
	//glDepthMask(GL_TRUE);

	SDL_EnableKeyRepeat(1, SDL_DEFAULT_REPEAT_INTERVAL / 3);

	// Initialize game
	m_engine = new GameEngine();
	m_engine->onInit();

	return true;
}

void Application::onCleanup() {
	if (m_engine) {
		m_engine->onCleanup();
		delete m_engine;
		m_engine = 0;
	}
	SDL_FreeSurface(m_display);
	m_display = 0;
}

BaseEngine * Application::engine() const {
	return m_engine;
}

ResourceManager * Application::manager() const {
	return m_manager;
}
