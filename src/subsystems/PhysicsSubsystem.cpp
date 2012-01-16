#include <algorithm>
#include <map>

#include "GameEngine.h"
#include "LuaCall.h"
#include "components/Body.h"
#include "subsystems/PhysicsSubsystem.h"
#include "subsystems/LuaSubsystem.h"

PhysicsSubsystem::PhysicsSubsystem(GameEngine *engine)
	: Subsystem(engine) {
	m_currTime = 0;
	m_timestep = 1.0f/70.0f;
	m_timeFactor = 1.0f;
	m_velocityIterations = 6;
	m_positionIterations = 2;
}

PhysicsSubsystem::~PhysicsSubsystem() {}

void PhysicsSubsystem::registerBody(Body::Ptr component) {
	m_bodies.push_back(component);

	if (m_world && !component->body()) {
		component->initBody(m_world.get());
	}
}

void PhysicsSubsystem::unregisterBody(Body::Ptr component) {
	auto it = std::find(m_bodies.begin(), m_bodies.end(), component);
	if (it == m_bodies.end())
		return;
	m_bodies.erase(it);

	if (m_world && component->body()) {
		component->destroyBody(m_world.get());
	}
}

bool PhysicsSubsystem::init() {
	m_currTime = engine()->time() / 1000.0;
	m_worldTimeAccumulator = 0;
	m_worldTime = 0;

	b2Vec2 gravity(0.0f, -15.0f);
	m_world = std::unique_ptr<b2World>(new b2World(gravity));
	m_world->SetContactListener(this);

	for (auto &component : m_bodies) {
		if (!component->body()) {
			component->initBody(m_world.get());
		}
	}

	return true;
}

void PhysicsSubsystem::update() {
	float time = engine()->time() / 1000.0;
	float elapsed = time - m_currTime;
	m_currTime = time;
	m_worldTimeAccumulator += elapsed * m_timeFactor;

	while (m_worldTimeAccumulator >= m_timestep) {
		m_worldTimeAccumulator -= m_timestep;
		m_worldTime += m_timestep;
		m_world->Step(m_timestep, m_velocityIterations, m_positionIterations);
		LuaCall::Ptr call = engine()->lua()->startGlobalCall("onPhysicsUpdate");
		if (call) {
			call->push(m_timestep);
			call->execute();
		}
	}
}

float PhysicsSubsystem::timeFactor() const {
	return m_timeFactor;
}

void PhysicsSubsystem::setTimeFactor(float timeFactor) {
	m_timeFactor = timeFactor;
}

void PhysicsSubsystem::BeginContact(b2Contact *contact) {
	Body *rawA = static_cast<Body *>(contact->GetFixtureA()->GetBody()->GetUserData());
	Body *rawB = static_cast<Body *>(contact->GetFixtureB()->GetBody()->GetUserData());

	Body::Ptr bodyA = rawA->shared_from_this();
	Body::Ptr bodyB = rawB->shared_from_this();

	LuaCall::Ptr call = engine()->lua()->startMethodCall("Body", bodyA, "onContactBegin");
	if (call) {
		call->push("Body", bodyB);
		call->execute();
	}
	call = 0;

	call = engine()->lua()->startMethodCall("Body", bodyB, "onContactBegin");
	if (call) {
		call->push("Body", bodyA);
		call->execute();
	}
}

void PhysicsSubsystem::EndContact(b2Contact *contact) {
	Body *rawA = static_cast<Body *>(contact->GetFixtureA()->GetBody()->GetUserData());
	Body *rawB = static_cast<Body *>(contact->GetFixtureB()->GetBody()->GetUserData());

	Body::Ptr bodyA = rawA->shared_from_this();
	Body::Ptr bodyB = rawB->shared_from_this();

	LuaCall::Ptr call = engine()->lua()->startMethodCall("Body", bodyA, "onContactEnd");
	if (call) {
		call->push("Body", bodyB);
		call->execute();
	}
	call = 0;

	call = engine()->lua()->startMethodCall("Body", bodyB, "onContactEnd");
	if (call) {
		call->push("Body", bodyA);
		call->execute();
	}
}
