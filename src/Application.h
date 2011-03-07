#ifndef APPLICATION_H
#define APPLICATION_H

#include <SDL/SDL.h>

class Application {
public:
	Application();

	bool running() const;
	void quit();
	bool execute();

	bool onInit();
	void onCleanup();

private:
	bool m_running;
	SDL_Surface * m_display;
};


#endif /* end of include guard: APPLICATION_H */
