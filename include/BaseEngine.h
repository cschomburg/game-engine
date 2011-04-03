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

protected:
	virtual bool onInit();
	virtual void onLoop();
	virtual void onRender();
	virtual void onCleanup();

private:
	bool m_running;
	int m_fps;
};

#endif /* end of include guard: BASEENGINE_H */
