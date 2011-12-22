#include <cstring>

#include "components/Body.h"
#include "lua/LuaClasses.h"

LuaClass luaBody("Body", &luaComponent);

int LuaBody_new(lua_State *L) {
	Object *object = static_cast<Object *>(luaObject.check(L, 1));
	lua_pop(L, 1);
	if (!object)
		return 0;

	Body *body= new Body(object);
	luaBody.push(L, body);
	return 1;
}

int LuaBody_setShape(lua_State *L) {
	Body *body = static_cast<Body *>(luaBody.check(L, 1));
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
	Body *body = static_cast<Body *>(luaBody.check(L, 1));
	lua_pop(L, 1);

	lua_pushnumber(L, body->pos().x);
	lua_pushnumber(L, body->pos().y);
	return 2;
}

int LuaBody_setPos(lua_State *L) {
	Body *body = static_cast<Body *>(luaBody.check(L, 1));
	float x = luaL_checknumber(L, 2);
	float y = luaL_checknumber(L, 3);
	lua_pop(L, 3);

	body->setPos(Vector2(x, y));
	return 0;
}

int LuaBody_angle(lua_State *L) {
	Body *body = static_cast<Body *>(luaBody.check(L, 1));
	lua_pop(L, 1);

	lua_pushnumber(L, body->angle());
	return 1;
}

int LuaBody_setAngle(lua_State *L) {
	Body *body = static_cast<Body *>(luaBody.check(L, 1));
	float angle = luaL_checknumber(L, 2);
	lua_pop(L, 2);

	body->setAngle(angle);
	return 0;
}

void LuaBody_classSetup(lua_State *L) {
	static const luaL_Reg methods[] = {
		{ "new", LuaBody_new },
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
