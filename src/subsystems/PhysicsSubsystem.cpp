#include <algorithm>
#include <map>

#include "Application.h"
#include "Component.h"
#include "components/Body.h"
#include "Object.h"
#include "subsystems/PhysicsSubsystem.h"

PhysicsSubsystem::PhysicsSubsystem(GameEngine *engine)
	: Subsystem(engine) {
	m_currTime = 0;
	m_timestep = 1.0f/60.0f;
	m_timeFactor = 1.0f;
	m_velocityIterations = 6;
	m_positionIterations = 2;

	engine->objectRegistered.connect(boost::bind(&PhysicsSubsystem::registerObject, this, _1));
	engine->objectUnregistered.connect(boost::bind(&PhysicsSubsystem::unregisterObject, this, _1));
}

PhysicsSubsystem::~PhysicsSubsystem() {}

void PhysicsSubsystem::registerObject(Object *object) {
	Body *component = object->component<Body>();
	if (!component)
		return;

	m_bodies.push_back(component);

	if (m_world && !component->body()) {
		component->initBody(m_world.get());
	}
}

void PhysicsSubsystem::unregisterObject(Object *object) {
	Body *component = object->component<Body>();
	if (!component)
		return;

	auto it = std::find(m_bodies.begin(), m_bodies.end(), component);
	if (it == m_bodies.end())
		return;
	m_bodies.erase(it);

	if (m_world && component->body()) {
		component->destroyBody(m_world.get());
	}
}

bool PhysicsSubsystem::init() {
	m_currTime = Application::instance()->time() / 1000.0;
	m_worldTimeAccumulator = 0;
	m_worldTime = 0;

	b2Vec2 gravity(0.0f, -15.0f);
	m_world = std::unique_ptr<b2World>(new b2World(gravity));

	for (auto &component : m_bodies) {
		if (!component->body() && component->object()->type() != ObjectType::Background) {
			component->initBody(m_world.get());
		}
	}

	return true;
}

void PhysicsSubsystem::update() {
	float time = Application::instance()->time() / 1000.0;
	float elapsed = time - m_currTime;
	m_currTime = time;
	m_worldTimeAccumulator += elapsed * m_timeFactor;

	while (m_worldTimeAccumulator >= m_timestep) {
		m_worldTimeAccumulator -= m_timestep;
		m_worldTime += m_timestep;
		m_world->Step(m_timestep, m_velocityIterations, m_positionIterations);
	}
}
