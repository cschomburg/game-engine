#include <cstring>
#include <string>

#include "GameEngine.h"
#include "components/Body.h"
#include "subsystems/PhysicsSubsystem.h"
#include "lua/LuaClasses.h"

LuaClass luaBody("Body", &luaComponent);

int LuaBody_new(lua_State *L) {
	luaBody.push(L, Body::Ptr(new Body()));
	return 1;
}

int LuaBody_register(lua_State *L) {
	Body::Ptr body = luaBody.check<Body>(L, 1);
	lua_pop(L, 1);

	GameEngine::instance()->physics()->registerBody(body);
	return 0;
}

int LuaBody_unregister(lua_State *L) {
	Body::Ptr body = luaBody.check<Body>(L, 1);
	lua_pop(L, 1);

	GameEngine::instance()->physics()->unregisterBody(body);
	return 0;
}

int LuaBody_type(lua_State *L) {
	Body::Ptr body = luaBody.check<Body>(L, 1);
	lua_pop(L, 1);

	lua_pushstring(L, body->type().c_str());
	return 1;
}

int LuaBody_setType(lua_State *L) {
	Body::Ptr body = luaBody.check<Body>(L, 1);
	std::string type(luaL_checkstring(L, 2));
	lua_pop(L, 2);

	body->setType(type);
	return 0;
}

int LuaBody_setShape(lua_State *L) {
	Body::Ptr body = luaBody.check<Body>(L, 1);
	const char *type = luaL_checkstring(L, 2);

	if (strcmp(type, "box") == 0) {
		float halfWidth = luaL_checknumber(L, 3);
		float halfHeight = luaL_checknumber(L, 4);
		lua_pop(L, 4);

		b2PolygonShape *shape = new b2PolygonShape();
		shape->SetAsBox(halfWidth, halfHeight);
		body->setShape(shape);
		return 0;
	}

	lua_pop(L, 2);
	return 0;
}

int LuaBody_pos(lua_State *L) {
	Body::Ptr body = luaBody.check<Body>(L, 1);
	lua_pop(L, 1);

	lua_pushnumber(L, body->pos().x);
	lua_pushnumber(L, body->pos().y);
	return 2;
}

int LuaBody_setPos(lua_State *L) {
	Body::Ptr body = luaBody.check<Body>(L, 1);
	float x = luaL_checknumber(L, 2);
	float y = luaL_checknumber(L, 3);
	lua_pop(L, 3);

	body->setPos(Vector2(x, y));
	return 0;
}

int LuaBody_angle(lua_State *L) {
	Body::Ptr body = luaBody.check<Body>(L, 1);
	lua_pop(L, 1);

	lua_pushnumber(L, body->angle());
	return 1;
}

int LuaBody_setAngle(lua_State *L) {
	Body::Ptr body = luaBody.check<Body>(L, 1);
	float angle = luaL_checknumber(L, 2);
	lua_pop(L, 2);

	body->setAngle(angle);
	return 0;
}

int LuaBody_worldCenter(lua_State *L) {
	Body::Ptr body = luaBody.check<Body>(L, 1);
	lua_pop(L, 1);
	if (!body->body())
		return 0;

	b2Vec2 point = body->body()->GetWorldCenter();
	lua_pushnumber(L, point.x);
	lua_pushnumber(L, point.y);
	return 2;
}

int LuaBody_localCenter(lua_State *L) {
	Body::Ptr body = luaBody.check<Body>(L, 1);
	lua_pop(L, 1);
	if (!body->body())
		return 0;
	
	b2Vec2 point = body->body()->GetLocalCenter();
	lua_pushnumber(L, point.x);
	lua_pushnumber(L, point.y);
	return 2;
}

int LuaBody_linearVelocity(lua_State *L) {
	Body::Ptr body = luaBody.check<Body>(L, 1);
	lua_pop(L, 1);
	if (!body->body())
		return 0;
	
	b2Vec2 v = body->body()->GetLinearVelocity();
	lua_pushnumber(L, v.x);
	lua_pushnumber(L, v.y);
	return 2;
}

int LuaBody_setLinearVelocity(lua_State *L) {
	Body::Ptr body = luaBody.check<Body>(L, 1);
	float x = luaL_checknumber(L, 2);
	float y = luaL_checknumber(L, 3);
	lua_pop(L, 3);
	if (!body->body())
		return 0;

	body->body()->SetLinearVelocity(b2Vec2(x, y));
	return 0;
}

int LuaBody_angularVelocity(lua_State *L) {
	Body::Ptr body = luaBody.check<Body>(L, 1);
	lua_pop(L, 1);

	lua_pushnumber(L, body->body()->GetAngularVelocity());
	return 1;
}

int LuaBody_setAngularVelocity(lua_State *L) {
	Body::Ptr body = luaBody.check<Body>(L, 1);
	float omega = luaL_checknumber(L, 2);
	lua_pop(L, 2);
	if (!body->body())
		return 0;

	body->body()->SetAngularVelocity(omega);
	return 0;
}

int LuaBody_applyForce(lua_State *L) {
	Body::Ptr body = luaBody.check<Body>(L, 1);
	b2Vec2 force(luaL_checknumber(L, 2), luaL_checknumber(L, 3));
	b2Vec2 point(luaL_checknumber(L, 4), luaL_checknumber(L, 5));
	lua_pop(L, 5);
	if (!body->body())
		return 0;

	body->body()->ApplyForce(force, point);
	return 0;
}

int LuaBody_applyForceToCenter(lua_State *L) {
	Body::Ptr body = luaBody.check<Body>(L, 1);
	b2Vec2 force(luaL_checknumber(L, 2), luaL_checknumber(L, 3));
	lua_pop(L, 3);
	if (!body->body())
		return 0;

	body->body()->ApplyForceToCenter(force);
	return 0;
}

int LuaBody_applyTorque(lua_State *L) {
	Body::Ptr body = luaBody.check<Body>(L, 1);
	float torque = luaL_checknumber(L, 2);
	lua_pop(L, 2);
	if (!body->body())
		return 0;

	body->body()->ApplyTorque(torque);
	return 0;
}

int LuaBody_applyLinearImpulse(lua_State *L) {
	Body::Ptr body = luaBody.check<Body>(L, 1);
	b2Vec2 impulse(luaL_checknumber(L, 2), luaL_checknumber(L, 3));
	b2Vec2 point(luaL_checknumber(L, 4), luaL_checknumber(L, 5));
	lua_pop(L, 5);
	if (!body->body())
		return 0;

	body->body()->ApplyLinearImpulse(impulse, point);
	return 0;
}

int LuaBody_applyAngularImpulse(lua_State *L) {
	Body::Ptr body = luaBody.check<Body>(L, 1);
	float impulse = luaL_checknumber(L, 2);
	lua_pop(L, 2);
	if (!body->body())
		return 0;

	body->body()->ApplyAngularImpulse(impulse);
	return 0;
}

int LuaBody_mass(lua_State *L) {
	Body::Ptr body = luaBody.check<Body>(L, 1);
	lua_pop(L, 1);

	lua_pushnumber(L, body->body()->GetMass());
	return 1;
}

int LuaBody_inertia(lua_State *L) {
	Body::Ptr body = luaBody.check<Body>(L, 1);
	lua_pop(L, 1);

	lua_pushnumber(L, body->body()->GetInertia());
	return 1;
}

int LuaBody_worldPoint(lua_State *L) {
	Body::Ptr body = luaBody.check<Body>(L, 1);
	b2Vec2 lPoint(luaL_checknumber(L, 2), luaL_checknumber(L, 3));
	lua_pop(L, 3);
	if (!body->body())
		return 0;

	b2Vec2 wPoint = body->body()->GetWorldPoint(lPoint);
	lua_pushnumber(L, wPoint.x);
	lua_pushnumber(L, wPoint.y);
	return 2;
}

int LuaBody_worldVector(lua_State *L) {
	Body::Ptr body = luaBody.check<Body>(L, 1);
	b2Vec2 lVector(luaL_checknumber(L, 2), luaL_checknumber(L, 3));
	lua_pop(L, 3);
	if (!body->body())
		return 0;

	b2Vec2 wVector = body->body()->GetWorldVector(lVector);
	lua_pushnumber(L, wVector.x);
	lua_pushnumber(L, wVector.y);
	return 2;
}

int LuaBody_localPoint(lua_State *L) {
	Body::Ptr body = luaBody.check<Body>(L, 1);
	b2Vec2 wPoint(luaL_checknumber(L, 2), luaL_checknumber(L, 3));
	lua_pop(L, 3);
	if (!body->body())
		return 0;

	b2Vec2 lPoint = body->body()->GetLocalPoint(wPoint);
	lua_pushnumber(L, lPoint.x);
	lua_pushnumber(L, lPoint.y);
	return 2;
}

int LuaBody_localVector(lua_State *L) {
	Body::Ptr body = luaBody.check<Body>(L, 1);
	b2Vec2 wVector(luaL_checknumber(L, 2), luaL_checknumber(L, 3));
	lua_pop(L, 3);
	if (!body->body())
		return 0;

	b2Vec2 lVector = body->body()->GetLocalVector(wVector);
	lua_pushnumber(L, lVector.x);
	lua_pushnumber(L, lVector.y);
	return 2;
}

int LuaBody_linearVelocityFromWorldPoint(lua_State *L) {
	Body::Ptr body = luaBody.check<Body>(L, 1);
	b2Vec2 wPoint(luaL_checknumber(L, 2), luaL_checknumber(L, 3));
	lua_pop(L, 3);
	if (!body->body())
		return 0;

	b2Vec2 velocity = body->body()->GetLinearVelocityFromWorldPoint(wPoint);
	lua_pushnumber(L, velocity.x);
	lua_pushnumber(L, velocity.y);
	return 2;
}

int LuaBody_linearVelocityFromLocalPoint(lua_State *L) {
	Body::Ptr body = luaBody.check<Body>(L, 1);
	b2Vec2 lPoint(luaL_checknumber(L, 2), luaL_checknumber(L, 3));
	lua_pop(L, 3);
	if (!body->body())
		return 0;

	b2Vec2 velocity = body->body()->GetLinearVelocityFromLocalPoint(lPoint);
	lua_pushnumber(L, velocity.x);
	lua_pushnumber(L, velocity.y);
	return 2;
}

int LuaBody_linearDamping(lua_State *L) {
	Body::Ptr body = luaBody.check<Body>(L, 1);
	lua_pop(L, 1);
	if (!body->body())
		return 0;

	lua_pushnumber(L, body->body()->GetLinearDamping());
	return 1;
}

int LuaBody_setLinearDamping(lua_State *L) {
	Body::Ptr body = luaBody.check<Body>(L, 1);
	float damping = luaL_checknumber(L, 2);
	lua_pop(L, 2);
	if (!body->body())
		return 0;

	body->body()->SetLinearDamping(damping);
	return 0;
}

int LuaBody_angularDamping(lua_State *L) {
	Body::Ptr body = luaBody.check<Body>(L, 1);
	lua_pop(L, 1);
	if (!body->body())
		return 0;

	lua_pushnumber(L, body->body()->GetAngularDamping());
	return 1;
}

int LuaBody_setAngularDamping(lua_State *L) {
	Body::Ptr body = luaBody.check<Body>(L, 1);
	float damping = luaL_checknumber(L, 2);
	lua_pop(L, 2);
	if (!body->body())
		return 0;

	body->body()->SetAngularDamping(damping);
	return 0;
}

int LuaBody_gravityScale(lua_State *L) {
	Body::Ptr body = luaBody.check<Body>(L, 1);
	lua_pop(L, 1);
	if (!body->body())
		return 0;

	lua_pushnumber(L, body->body()->GetGravityScale());
	return 1;
}

int LuaBody_setGravityScale(lua_State *L) {
	Body::Ptr body = luaBody.check<Body>(L, 1);
	float scale = luaL_checknumber(L, 2);
	lua_pop(L, 2);
	if (!body->body())
		return 0;

	body->body()->SetGravityScale(scale);
	return 0;
}

int LuaBody_isBullet(lua_State *L) {
	Body::Ptr body = luaBody.check<Body>(L, 1);
	lua_pop(L, 1);
	if (!body->body())
		return 0;

	lua_pushboolean(L, body->body()->IsBullet());
	return 1;
}

int LuaBody_setBullet(lua_State *L) {
	Body::Ptr body = luaBody.check<Body>(L, 1);
	bool flag = !lua_isnil(L, 2);
	lua_pop(L, 2);
	if (!body->body())
		return 0;

	body->body()->SetBullet(flag);
	return 0;
}

int LuaBody_isSleepingAllowed(lua_State *L) {
	Body::Ptr body = luaBody.check<Body>(L, 1);
	lua_pop(L, 1);
	if (!body->body())
		return 0;

	lua_pushboolean(L, body->body()->IsSleepingAllowed());
	return 1;
}

int LuaBody_setSleepingAllowed(lua_State *L) {
	Body::Ptr body = luaBody.check<Body>(L, 1);
	bool flag = !lua_isnil(L, 2);
	lua_pop(L, 2);
	if (!body->body())
		return 0;

	body->body()->SetSleepingAllowed(flag);
	return 0;
}

int LuaBody_isAwake(lua_State *L) {
	Body::Ptr body = luaBody.check<Body>(L, 1);
	lua_pop(L, 1);
	if (!body->body())
		return 0;

	lua_pushboolean(L, body->body()->IsAwake());
	return 1;
}

int LuaBody_setAwake(lua_State *L) {
	Body::Ptr body = luaBody.check<Body>(L, 1);
	bool flag = !lua_isnil(L, 2);
	lua_pop(L, 2);
	if (!body->body())
		return 0;

	body->body()->SetAwake(flag);
	return 0;
}

int LuaBody_isFixedRotation(lua_State *L) {
	Body::Ptr body = luaBody.check<Body>(L, 1);
	lua_pop(L, 1);
	if (!body->body())
		return 0;

	lua_pushboolean(L, body->body()->IsFixedRotation());
	return 1;
}

int LuaBody_setFixedRotation(lua_State *L) {
	Body::Ptr body = luaBody.check<Body>(L, 1);
	bool flag = !lua_isnil(L, 2);
	lua_pop(L, 2);
	if (!body->body())
		return 0;

	body->body()->SetFixedRotation(flag);
	return 0;
}

void LuaBody_classSetup(lua_State *L) {
	static const luaL_Reg methods[] = {
		{ "new", LuaBody_new },
		{ "register", LuaBody_register },
		{ "unregister", LuaBody_unregister },
		{ "type", LuaBody_type },
		{ "setType", LuaBody_setType },
		{ "setShape", LuaBody_setShape },
		{ "pos", LuaBody_pos },
		{ "setPos", LuaBody_setPos },
		{ "angle", LuaBody_angle },
		{ "setAngle", LuaBody_setAngle},
		{ "worldCenter", LuaBody_worldCenter },
		{ "localCenter", LuaBody_localCenter },
		{ "linearVelocity", LuaBody_linearVelocity },
		{ "setLinearVelocity", LuaBody_setLinearVelocity },
		{ "angularVelocity", LuaBody_angularVelocity },
		{ "setAngularVelocity", LuaBody_setAngularVelocity },
		{ "applyForce", LuaBody_applyForce },
		{ "applyForceToCenter", LuaBody_applyForceToCenter },
		{ "applyTorque", LuaBody_applyTorque },
		{ "applyLinearImpulse", LuaBody_applyLinearImpulse },
		{ "applyAngularImpulse", LuaBody_applyAngularImpulse },
		{ "mass", LuaBody_mass},
		{ "inertia", LuaBody_inertia },
		{ "worldPoint", LuaBody_worldPoint },
		{ "worldVector", LuaBody_worldVector },
		{ "localPoint", LuaBody_localPoint },
		{ "localVector", LuaBody_localVector },
		{ "linearVelocityFromWorldPoint", LuaBody_linearVelocityFromWorldPoint },
		{ "linearVelocityFromLocalPoint", LuaBody_linearVelocityFromLocalPoint },
		{ "linearDamping", LuaBody_linearDamping},
		{ "setLinearDamping", LuaBody_setLinearDamping },
		{ "angularDamping", LuaBody_angularDamping },
		{ "setAngularDamping", LuaBody_setAngularDamping },
		{ "gravityScale", LuaBody_gravityScale },
		{ "setGravityScale", LuaBody_setGravityScale },
		{ "isBullet", LuaBody_isBullet},
		{ "setBullet", LuaBody_setBullet },
		{ "isSleepingAllowed", LuaBody_isSleepingAllowed },
		{ "setSleepingAllowed", LuaBody_setSleepingAllowed },
		{ "isAwake", LuaBody_isAwake },
		{ "setAwake", LuaBody_setAwake },
		{ "isFixedRotation", LuaBody_isFixedRotation },
		{ "setFixedRotation", LuaBody_setFixedRotation },
		{ 0, 0 },
	};

	static const luaL_Reg meta[] = {
		{ 0, 0 },
	};

	luaBody.registerClass(L, methods, meta);
}
