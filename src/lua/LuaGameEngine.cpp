#include <boost/filesystem.hpp>

#include "GameEngine.h"
#include "lua/LuaClasses.h"

LuaClass luaGameEngine("GameEngine");

int LuaGameEngine_fileModified(lua_State *L) {
	std::string path(luaL_checkstring(L, 1));
	lua_pushnumber(L, boost::filesystem::last_write_time(path));
	return 1;
}

int LuaGameEngine_setKeyRepeat(lua_State *L) {
	int delay = luaL_checkint(L, 1);
	int interval = luaL_checkint(L, 2);

	SDL_EnableKeyRepeat(delay, interval);

	return 0;
}

void LuaGameEngine_classSetup(lua_State *L) {
	static const luaL_Reg methods[] = {
		{ "fileModified", LuaGameEngine_fileModified },
		{ "setKeyRepeat", LuaGameEngine_setKeyRepeat },
		{ 0, 0 },
	};

	static const luaL_Reg meta[] = {
		{ 0, 0 },
	};

	luaGameEngine.registerClass(L, methods, meta);
}
