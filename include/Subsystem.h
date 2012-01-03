#ifndef SUBSYSTEM_H
#define SUBSYSTEM_H

#include "GameEngine.h"

class Subsystem {
public:
	Subsystem(GameEngine *engine);
	virtual ~Subsystem();

	GameEngine *engine() const;

	virtual bool init();
	virtual void update();
	virtual void destroy();

private:
	GameEngine *m_engine;
};


#endif /* end of include guard: SUBSYSTEM_H */
