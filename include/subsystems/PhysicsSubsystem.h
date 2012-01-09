#ifndef PHYSICSSUBSYSTEM_H
#define PHYSICSSUBSYSTEM_H

#include <memory>
#include <Box2D/Box2D.h>

#include "Subsystem.h"
#include "components/Body.h"

class GameEngine;

class PhysicsSubsystem : public Subsystem, public b2ContactListener {
public:
	PhysicsSubsystem(GameEngine *engine);
	virtual ~PhysicsSubsystem();

	bool init();
	void update();

	void registerBody(Body::Ptr component);
	void unregisterBody(Body::Ptr component);

	float timeFactor() const;
	void setTimeFactor(float timeFactor);

	virtual void BeginContact(b2Contact *contact);
	virtual void EndContact(b2Contact *contact);

private:
	std::vector<Body::Ptr> m_bodies;
	std::unique_ptr<b2World> m_world;

	int m_velocityIterations;
	int m_positionIterations;
	float m_currTime;
	float m_timeFactor;
	float m_worldTimeAccumulator;
	float m_timestep;
	float m_worldTime;
};

#endif /* end of include guard: PHYSICSSUBSYSTEM_H */
