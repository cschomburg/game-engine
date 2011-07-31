#include <iostream>
#include "lua/LuaObject.h"
#include "Object.h"

LuaClass luaObject("Object");

int LuaObject_helloWorld(lua_State *L) {
	std::cout << "Hello, world!\n";
	return 0;
}

int LuaObject_testFunction(lua_State *L) {
	Object *object = (Object *)luaObject.check(L, 1);
	lua_pop(L, 1);
	lua_pushliteral(L, "success!");
	return 1;
}

void LuaObject_classSetup(lua_State *L) {
	static const luaL_Reg methods[] = {
		{ "helloWorld", LuaObject_helloWorld },
		{ "testFunction", LuaObject_testFunction },
		{ 0, 0 },
	};

	static const luaL_Reg meta[] = {
		{ 0, 0 },
	};

	luaObject.registerClass(L, methods, meta);
}
