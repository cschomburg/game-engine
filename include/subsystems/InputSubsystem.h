#ifndef INPUTSUBSYSTEM_H
#define INPUTSUBSYSTEM_H

#include <SDL/SDL.h>

#include "Subsystem.h"

class Object;

class InputSubsystem : public Subsystem {
public:
	InputSubsystem(GameEngine *engine);
	virtual ~InputSubsystem();

	void update();
};

#endif /* end of include guard: INPUTSUBSYSTEM_H */
