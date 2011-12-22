#include <iostream>
#include <string>

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

#include "Application.h"
#include "subsystems/LuaSubsystem.h"
#include "LuaClass.h"
#include "lua/LuaClasses.h"

LuaSubsystem::LuaSubsystem(GameEngine *engine)
	: Subsystem(engine) {
	L = 0;
	m_lastTime = 0;
}

LuaSubsystem::~LuaSubsystem() {}

bool LuaSubsystem::init() {
	if (L)
		return true;

	L = lua_open();
	luaL_openlibs(L);

	LuaGameEngine_classSetup(L);
	LuaComponent_classSetup(L);
	LuaBody_classSetup(L);
	LuaRenderable_classSetup(L);
	LuaObject_classSetup(L);

	m_lastTime = Application::instance()->time();
	return true;
}

void LuaSubsystem::destroy() {
	if (L) {
		lua_close(L);
		L = 0;
	}
}

void LuaSubsystem::update() {
	int time = Application::instance()->time();
	float elapsed = float(time - m_lastTime) / 1000;
	m_lastTime = time;

	lua_getfield(L, LUA_GLOBALSINDEX, "OnUpdate");
	lua_pushnumber(L, elapsed);
	int status = lua_pcall(L, 1, 0, 0);
	if (status != 0) {
		printError(status);
	}
}

lua_State *LuaSubsystem::state() const {
	return L;
}

bool LuaSubsystem::loadFile(const std::string &file) {
	int status = luaL_loadfile(L, file.c_str());
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

void LuaSubsystem::printError(int status) const {
	if (status != 0) {
		std::cout << "Lua err: " << lua_tostring(L, -1) << std::endl;
		lua_pop(L, 1);
	}
}

void LuaSubsystem::push(const std::string &className, void *instance, const char *field) {
	LuaClass *luaClass = LuaClass::get(className);
	if (!luaClass)
		return;
	luaClass->push(L, instance);

	lua_pushstring(L, field);
	lua_pushvalue(L, -2); // Dup table
	lua_rawset(L, LUA_GLOBALSINDEX); // globals[field] = table

	lua_pop(L, -1);
}
