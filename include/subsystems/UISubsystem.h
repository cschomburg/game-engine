#ifndef INTERFACESUBSYSTEM_H
#define INTERFACESUBSYSTEM_H

#include <memory>
#include <SDL/SDL.h>

#include "Subsystem.h"

class Widget;

class UISubsystem : public Subsystem {
public:
	UISubsystem(GameEngine *engine);
	virtual ~UISubsystem();

	bool init();
	void update();

	void render();

	std::shared_ptr<Widget> rootWidget() const;

private:
	void renderTree(std::shared_ptr<Widget> widget);

private:
	std::shared_ptr<Widget> m_rootWidget;
};

#endif /* end of include guard: INTERFACESUBSYSTEM_H */
