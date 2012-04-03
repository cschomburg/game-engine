#include "Box2DCompat.h"
#include "components/Body.h"

Body::Body() {
	m_angle = 0;
	m_body = 0;
	m_shape = 0;
	m_type = "dynamic";
}

Body::~Body() {
	if (m_shape) {
		delete m_shape;
		m_shape = 0;
	}
}

b2BodyDef Body::def() const {
	b2BodyDef def;
	if (m_type == "dynamic") {
		def.type = b2_dynamicBody;
		def.allowSleep = false;
	} else if (m_type == "static") {
		def.type = b2_staticBody;
	} else if (m_type == "kinematic") {
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
	b2BodyDef d = def();
	m_body = world->CreateBody(&d);
	m_body->SetUserData(this);
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

std::string Body::type() const {
	return m_type;
}

void Body::setType(const std::string &type) {
	m_type = type;
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
