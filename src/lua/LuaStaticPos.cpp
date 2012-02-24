#include "components/StaticPos.h"
#include "lua/LuaClasses.h"

LuaClass luaStaticPos("StaticPos", &luaComponent);

int LuaStaticPos_new(lua_State *L) {
	luaStaticPos.push(L, std::make_shared<StaticPos>());
	return 1;
}

int LuaStaticPos_pos(lua_State *L) {
	StaticPos::Ptr pos = luaStaticPos.check<StaticPos>(L, 1);
	lua_pop(L, 1);

	lua_pushnumber(L, pos->pos().x);
	lua_pushnumber(L, pos->pos().y);
	return 2;
}

int LuaStaticPos_setPos(lua_State *L) {
	StaticPos::Ptr pos = luaStaticPos.check<StaticPos>(L, 1);
	float x = luaL_checknumber(L, 2);
	float y = luaL_checknumber(L, 3);
	lua_pop(L, 3);

	pos->setPos(Vector2(x, y));
	return 0;
}

int LuaStaticPos_angle(lua_State *L) {
	StaticPos::Ptr pos = luaStaticPos.check<StaticPos>(L, 1);
	lua_pop(L, 1);

	lua_pushnumber(L, pos->angle());
	return 1;
}

int LuaStaticPos_setAngle(lua_State *L) {
	StaticPos::Ptr pos = luaStaticPos.check<StaticPos>(L, 1);
	float angle = luaL_checknumber(L, 2);
	lua_pop(L, 2);

	pos->setAngle(angle);
	return 0;
}

void LuaStaticPos_classSetup(lua_State *L) {
	static const luaL_Reg methods[] = {
		{ "new", LuaStaticPos_new },
		{ "pos", LuaStaticPos_pos },
		{ "setPos", LuaStaticPos_setPos },
		{ "angle", LuaStaticPos_angle },
		{ "setAngle", LuaStaticPos_setAngle},
		{ 0, 0 },
	};

	static const luaL_Reg meta[] = {
		{ 0, 0 },
	};

	luaStaticPos.registerClass(L, methods, meta);
}
