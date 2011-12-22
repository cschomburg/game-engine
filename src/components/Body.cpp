#include "Box2DCompat.h"
#include "components/Body.h"
#include "Object.h"

const ComponentType Body::componentType = "Body";

Body::Body(Object *object)
	: Component(componentType, object) {
	m_angle = 0;
	m_body = 0;
	m_shape = 0;
}

Body::~Body() {
	if (m_shape) {
		delete m_shape;
		m_shape = 0;
	}
}

b2BodyDef Body::def() const {
	b2BodyDef def;
	if (object()->type() == ObjectType::Dynamic) {
		def.type = b2_dynamicBody;
		def.allowSleep = false;
	} else if (object()->type() == ObjectType::Static) {
		def.type = b2_staticBody;
	} else if (object()->type() == ObjectType::Kinematic) {
		def.type = b2_kinematicBody;
	}
	def.position = toBox2D(m_pos);
	def.angle = m_angle;
	return def;
}

void Body::save() {
	m_pos = fromBox2D(m_body->GetPosition());
	m_angle = m_body->GetAngle();
}

b2Body *Body::body() const {
	return m_body;
}

void Body::initBody(b2World *world) {
	if (m_body || object()->type() == ObjectType::Background)
		return;
	b2BodyDef d = def();
	m_body = world->CreateBody(&d);
	if (m_shape) {
		m_body->CreateFixture(m_shape, 1.0f);
	}
}

void Body::destroyBody(b2World *world) {
	if (!m_body)
		return;
	save();
	world->DestroyBody(m_body);
	m_body = 0;
}

void Body::setShape(b2Shape *shape) {
	if (m_shape)
		delete m_shape;
	m_shape = shape;
}

Vector2 Body::pos() const {
	if (m_body) {
		return fromBox2D(m_body->GetPosition());
	} else {
		return m_pos;
	}
}

void Body::setPos(const Vector2 &pos) {
	if (m_body) {
		m_body->SetTransform(toBox2D(pos), m_body->GetAngle());
	} else {
		m_pos = pos;
	}
}

float Body::angle() const {
	if (m_body) {
		return m_body->GetAngle();
	} else {
		return m_angle;
	}
}

void Body::setAngle(float angle) {
	if (m_body) {
		m_body->SetTransform(m_body->GetPosition(), angle);
	} else {
		m_angle = angle;
	}
}
