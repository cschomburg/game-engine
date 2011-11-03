#include <deque>
#include <set>

#include "Subsystem.h"

class Movable;
class Collidable;

struct Collision {
	Collidable *a;
	Collidable *b;
	Vector2 vector;
};

class PhysicsSubsystem : public Subsystem {
public:
	PhysicsSubsystem(GameEngine *engine);
	virtual ~PhysicsSubsystem();

	virtual bool init();
	virtual void update();

	void registerComponent(Movable *component);
	void registerComponent(Collidable *component);
	void unregisterComponent(Movable *component);
	void unregisterComponent(Collidable *component);

private:
	void handleMovements(double dt);
	void handleCollisions();

private:
	double m_currTime;
	double m_timeAccumulator;
	double m_dt;
	double m_t;
	double m_timestep;

	std::set<Movable *> m_movables;
	std::set<Collidable *> m_collidables;
	std::deque<Collidable *> m_collisionUpdates;
};
