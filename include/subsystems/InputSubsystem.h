#ifndef INPUTSUBSYSTEM_H
#define INPUTSUBSYSTEM_H

#include <map>
#include <SDL/SDL.h>

#include "Subsystem.h"

class InputSubsystem : public Subsystem {
public:

	InputSubsystem(GameEngine *engine);
	virtual ~InputSubsystem();

	bool init();
	void update();

private:
	void handleEvent(SDL_Event *event);
	void simpleCall(const std::string &event);

	std::vector<std ::string> modToString(SDLMod mod);

private:
	static std::map<int, std::string> modMap;
};

#endif /* end of include guard: INPUTSUBSYSTEM_H */
