#ifndef APPLICATION_H
#define APPLICATION_H

#include "GameEngine.h"
#include "ResourceManager.h"

class SDL_Surface;

class Application {
public:
	Application();
	static Application * instance();

	bool running() const;
	void quit();
	bool execute();

	int time() const;

	bool windowed() const;
	int displayWidth() const;
	int displayHeight() const;

	GameEngine *engine() const;
	ResourceManager * manager() const;

private:
	bool init();
	void destroy();

private:
	bool m_running;
	int m_fps;

	bool m_windowed;
	int m_displayWidth;
	int m_displayHeight;

	GameEngine *m_engine;
	ResourceManager *m_manager;
	SDL_Surface *m_display;
};

#endif /* end of include guard: APPLICATION_H */
