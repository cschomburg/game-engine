#include <memory>
#include <Box2D/Box2D.h>

#include "GameEngine.h"
#include "Subsystem.h"
#include "components/Body.h"

class PhysicsSubsystem : public Subsystem {
public:
	PhysicsSubsystem(GameEngine *engine);
	virtual ~PhysicsSubsystem();

	bool init();
	void update();

	void registerBody(Body::Ptr component);
	void unregisterBody(Body::Ptr component);

	float timeFactor() const;
	void setTimeFactor(float timeFactor);

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
