#ifndef BODY_H
#define BODY_H

#include <memory>
#include <Box2D/Box2D.h>
#include "Component.h"
#include "interfaces/IPositionable.h"
#include "Vector2.h"

class Body : public Component, public IPositionable,
             public std::enable_shared_from_this<Body> {
public:
	typedef std::shared_ptr<Body> Ptr;

	Body(const std::string &objectID);
	virtual ~Body();

	b2BodyDef def() const;
	void save();

	b2Body *body() const;
	void initBody(b2World *world);
	void destroyBody(b2World *world);

	void setShape(b2Shape *shape);

	std::string type() const;
	void setType(const std::string &type);

	Vector2 pos() const;
	void setPos(const Vector2 &pos);
	float angle() const;
	void setAngle(float angle);

private:
	std::string m_type;
	Vector2 m_pos;
	float m_angle;
	b2BodyDef m_def;
	b2Body *m_body;
	b2Shape *m_shape;
};

#endif /* end of include guard: BODY_H */
