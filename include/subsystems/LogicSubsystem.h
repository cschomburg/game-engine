#ifndef LOGICSUBSYSTEM_H
#define LOGICSUBSYSTEM_H

#include <set>

#include "Subsystem.h"

class Updatable;

class LogicSubsystem : public Subsystem {
public:
	LogicSubsystem(GameEngine *engine);
	virtual ~LogicSubsystem();

	virtual void update();

	void registerComponent(Updatable *component);
	void unregisterComponent(Updatable *component);

private:
	std::set<Updatable *> m_updatables;
};

#endif /* end of include guard: LOGICSUBSYSTEM_H */
