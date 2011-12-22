#include <memory>
#include <Box2D/Box2D.h>

#include "Subsystem.h"

class Body;
class Object;

class PhysicsSubsystem : public Subsystem {
public:
	PhysicsSubsystem(GameEngine *engine);
	virtual ~PhysicsSubsystem();

	virtual bool init();
	virtual void update();

	void registerObject(Object *object);
	void unregisterObject(Object *object);

private:
	std::vector<Body *> m_bodies;
	std::unique_ptr<b2World> m_world;

	int m_velocityIterations;
	int m_positionIterations;
	float m_currTime;
	float m_timeFactor;
	float m_worldTimeAccumulator;
	float m_timestep;
	float m_worldTime;
};
