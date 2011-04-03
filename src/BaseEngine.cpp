#include <SDL/SDL_opengl.h>

#include "BaseEngine.h"

BaseEngine::BaseEngine() {
	m_running = false;
	m_fps = 0;
}

BaseEngine::~BaseEngine() {}

bool BaseEngine::running() const {
	return m_running;
}

void BaseEngine::quit() {
	m_running = false;
}

bool BaseEngine::execute() {
	if (!onInit()) {
		return false;
	}

	m_running = true;
	SDL_Event event;

	Uint32 lastTime = SDL_GetTicks();
	int frameCount = 0;

	while (m_running) {
		while (SDL_PollEvent(&event)) {
			onEvent(&event);
		}

		frameCount++;
		if ((SDL_GetTicks() - lastTime) >= 1000) {
			m_fps = frameCount;
			frameCount = 0;
			lastTime = SDL_GetTicks();
		}

		onLoop();
		onRender();
		SDL_GL_SwapBuffers();
	}

	onCleanup();
	return true;
}

bool BaseEngine::onInit() {
	return true;
}

void BaseEngine::onLoop() {}

void BaseEngine::onRender() {
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void BaseEngine::onCleanup() {}
