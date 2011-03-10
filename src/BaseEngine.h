#ifndef BASEENGINE_H
#define BASEENGINE_H

#include <SDL/SDL.h>

#include "Event.h"

class BaseEngine : public Event {
public:
	BaseEngine();
	virtual ~BaseEngine();

	bool running() const;
	void quit();
	bool execute();

	SDL_Surface * display() const;
	void setDisplay(SDL_Surface * display);

protected:
	virtual bool onInit();
	virtual void onLoop();
	virtual void onRender();
	virtual void onCleanup();

private:
	bool m_running;
	SDL_Surface * m_display;
};

#endif /* end of include guard: BASEENGINE_H */
