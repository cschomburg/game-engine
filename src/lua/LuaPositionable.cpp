#include <cstring>
#include <string>

#include "components/Positionable.h"
#include "lua/LuaClasses.h"

LuaClass luaPositionable("Positionable");

int LuaPositionable_new(lua_State *L) {
	luaPositionable.push(L, std::make_shared<Positionable>());
	return 1;
}

int LuaPositionable_pos(lua_State *L) {
	Positionable::Ptr positionable = luaPositionable.check<Positionable>(L, 1);
	lua_pop(L, 1);

	lua_pushnumber(L, positionable->pos().x);
	lua_pushnumber(L, positionable->pos().y);
	return 2;
}

int LuaPositionable_setPos(lua_State *L) {
	Positionable::Ptr positionable = luaPositionable.check<Positionable>(L, 1);
	float x = luaL_checknumber(L, 2);
	float y = luaL_checknumber(L, 3);
	lua_pop(L, 3);

	positionable->setPos(Vector2(x, y));
	return 0;
}

int LuaPositionable_angle(lua_State *L) {
	Positionable::Ptr positionable = luaPositionable.check<Positionable>(L, 1);
	lua_pop(L, 1);

	lua_pushnumber(L, positionable->angle());
	return 1;
}

int LuaPositionable_setAngle(lua_State *L) {
	Positionable::Ptr positionable = luaPositionable.check<Positionable>(L, 1);
	float angle = luaL_checknumber(L, 2);
	lua_pop(L, 2);

	positionable->setAngle(angle);
	return 0;
}

int LuaPositionable_anchor(lua_State *L) {
	Positionable::Ptr positionable = luaPositionable.check<Positionable>(L, 1);

	luaPositionable.push(L, positionable->anchor());
	return 1;
}

int LuaPositionable_setAnchor(lua_State *L) {
	Positionable::Ptr positionable = luaPositionable.check<Positionable>(L, 1);
	Positionable::Ptr anchor = luaPositionable.check<Positionable>(L, 2);

	positionable->setAnchor(anchor);
	return 0;
}

int LuaPositionable_worldPos(lua_State *L) {
	Positionable::Ptr positionable = luaPositionable.check<Positionable>(L, 1);
	lua_pop(L, 1);

	Vector2 worldPos = positionable->worldPos();
	lua_pushnumber(L, worldPos.x);
	lua_pushnumber(L, worldPos.y);
	return 2;
}

void LuaPositionable_classSetup(lua_State *L) {
	static const luaL_Reg methods[] = {
		{ "new", LuaPositionable_new },
		{ "pos", LuaPositionable_pos },
		{ "setPos", LuaPositionable_setPos },
		{ "angle", LuaPositionable_angle },
		{ "setAngle", LuaPositionable_setAngle},
		{ "anchor", LuaPositionable_anchor},
		{ "setAnchor", LuaPositionable_setAnchor},
		{ "worldPos", LuaPositionable_worldPos},
		{ 0, 0 },
	};

	static const luaL_Reg meta[] = {
		{ 0, 0 },
	};

	luaPositionable.registerClass(L, methods, meta);
}
