#include <cstring>
#include <string>

#include "GameEngine.h"
#include "components/Body.h"
#include "subsystems/PhysicsSubsystem.h"
#include "lua/LuaClasses.h"

LuaClass luaBody("Body", &luaComponent);

int LuaBody_new(lua_State *L) {
	std::string name(luaL_checkstring(L, 1));
	lua_pop(L, 1);

	luaBody.push(L, Body::Ptr(new Body(name)));
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
		{ 0, 0 },
	};

	static const luaL_Reg meta[] = {
		{ 0, 0 },
	};

	luaBody.registerClass(L, methods, meta);
}
