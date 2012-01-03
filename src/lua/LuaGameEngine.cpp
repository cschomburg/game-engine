#include "GameEngine.h"
#include "lua/LuaClasses.h"

LuaClass luaGameEngine("GameEngine");

void LuaGameEngine_classSetup(lua_State *L) {
	static const luaL_Reg methods[] = {
		{ 0, 0 },
	};

	static const luaL_Reg meta[] = {
		{ 0, 0 },
	};

	luaGameEngine.registerClass(L, methods, meta);
}
