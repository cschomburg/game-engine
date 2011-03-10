#include "BaseEngine.h"

BaseEngine::BaseEngine() {
	m_running = false;
	m_display = 0;
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
	while (m_running) {
		while (SDL_PollEvent(&event)) {
			onEvent(&event);
		}

		onLoop();
		onRender();
		SDL_Flip(m_display);
	}

	onCleanup();
	return true;
}

SDL_Surface * BaseEngine::display() const {
	return m_display;
}

void BaseEngine::setDisplay(SDL_Surface * display) {
	m_display = display;
}

bool BaseEngine::onInit() {
	return true;
}

void BaseEngine::onLoop() {}

void BaseEngine::onRender() {
	SDL_Rect rect;
	rect.x = 0;
	rect.y = 0;
	rect.w = m_display->w;
	rect.h = m_display->h;

	SDL_FillRect(m_display, &rect, SDL_MapRGB(m_display->format, 255, 255, 255));
}

void BaseEngine::onCleanup() {}
