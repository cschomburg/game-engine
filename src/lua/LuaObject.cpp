#include "lua/LuaObject.h"
#include "Object.h"

LuaClass luaObject("Object");

int LuaObject_name(lua_State *L) {
	Object *object = static_cast<Object *>(luaObject.check(L, 1));
	lua_pop(L, 1);

	lua_pushstring(L, object->name().c_str());
	return 1;
}

int LuaObject_setName(lua_State *L) {
	Object *object = static_cast<Object *>(luaObject.check(L, 1));
	const char *name = luaL_checkstring(L, 2);
	lua_pop(L, 2);

	object->setName(name);

	return 1;
}

void LuaObject_classSetup(lua_State *L) {
	static const luaL_Reg methods[] = {
		{ "name", LuaObject_name },
		{ "setName", LuaObject_setName },
		{ 0, 0 },
	};

	static const luaL_Reg meta[] = {
		{ 0, 0 },
	};

	luaObject.registerClass(L, methods, meta);
}
