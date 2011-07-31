#include "lua/LuaComponent.h"
#include "lua/LuaPositionable.h"
#include "components/Positionable.h"

LuaClass luaPositionable("Positionable", &luaComponent);

int LuaPositionable_pos(lua_State *L) {
	Positionable *positionable = static_cast<Positionable *>(luaPositionable.check(L, 1));
	lua_pop(L, 1);

	lua_pushnumber(L, positionable->pos().x);
	lua_pushnumber(L, positionable->pos().y);
	return 2;
}

int LuaPositionable_setPos(lua_State *L) {
	Positionable *positionable = static_cast<Positionable *>(luaPositionable.check(L, 1));
	int x = luaL_checknumber(L, 2);
	int y = luaL_checknumber(L, 3);
	lua_pop(L, 3);

	positionable->setPos(Vector2(x, y));

	return 0;
}

int LuaPositionable_modifyPos(lua_State *L) {
	Positionable *positionable = static_cast<Positionable *>(luaPositionable.check(L, 1));
	int x = luaL_checknumber(L, 2);
	int y = luaL_checknumber(L, 3);
	lua_pop(L, 3);

	positionable->modifyPos(Vector2(x, y));

	return 0;
}

void LuaPositionable_classSetup(lua_State *L) {
	static const luaL_Reg methods[] = {
		{ "pos", LuaPositionable_pos },
		{ "setPos", LuaPositionable_setPos },
		{ "modifyPos", LuaPositionable_modifyPos },
		{ 0, 0 },
	};

	static const luaL_Reg meta[] = {
		{ 0, 0 },
	};

	luaPositionable.registerClass(L, methods, meta);
}
