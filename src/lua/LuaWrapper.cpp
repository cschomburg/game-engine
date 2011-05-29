#include <iostream>

#include "Application.h"
#include "lua/LuaWrapper.h"

LuaWrapper::LuaWrapper() {
	L = 0;
	m_lastTime = 0;
}

LuaWrapper::~LuaWrapper() {
	destroy();
}

bool LuaWrapper::init() {
	if (L)
		return true;

	L = lua_open();
	luaL_openlibs(L);

	m_lastTime = Application::instance()->time();
	return true;
}

void LuaWrapper::destroy() {
	if (L) {
		lua_close(L);
		L = 0;
	}
}

lua_State * LuaWrapper::state() const {
	return L;
}

bool LuaWrapper::loadFile(const char * file) {
	int status = luaL_loadfile(L, file);
	if (status != 0) {
		printError(status);
		return false;
	}

	status = lua_pcall(L, 0, LUA_MULTRET, 0);
	if (status != 0) {
		printError(status);
		return false;
	}

	return true;
}

bool LuaWrapper::update() {
	Uint32 time = Application::instance()->time();
	float elapsed = float(time - m_lastTime) / 1000;
	m_lastTime = time;

	lua_getfield(L, LUA_GLOBALSINDEX, "onUpdate");
	lua_pushnumber(L, elapsed);
	lua_call(L, 1, 0);
}

void LuaWrapper::printError(int status) {
	if (status != 0) {
		std::cout << "Lua err: " << lua_tostring(L, -1) << std::endl;
		lua_pop(L, 1);
	}
}
