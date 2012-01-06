#include <iostream>
#include <string>

#include "Lua.h"
#include "subsystems/LuaSubsystem.h"
#include "LuaCall.h"
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
	LuaGraphics_classSetup(L);

	LuaComponent_classSetup(L);
	LuaBody_classSetup(L);
	LuaRenderable_classSetup(L);
	LuaStaticPos_classSetup(L);

	m_lastTime = engine()->time();
	return true;
}

void LuaSubsystem::destroy() {
	if (L) {
		lua_close(L);
		L = 0;
	}
}

void LuaSubsystem::update() {
	int time = engine()->time();
	float elapsed = float(time - m_lastTime) / 1000.0f;
	m_lastTime = time;

	LuaCall::Ptr call = startGlobalCall("onUpdate");
	if (call) {
		call->push(elapsed);
		call->execute();
	}
}

bool LuaSubsystem::loadFile(const std::string &file) {
	int status = luaL_loadfile(L, file.c_str());
	if (status == 0) {
		status = lua_pcall(L, 0, 0, 0);
	}
	if (status != 0) {
		std::cout << "Lua err: " << lua_tostring(L, -1) << std::endl;
		lua_pop(L, 1);
		return false;
	}

	return true;
}

std::shared_ptr<LuaCall> LuaSubsystem::startCall(const std::string &ident) {
	LuaCall::Ptr call = m_lastCall.lock();
	if (call) {
		std::cout << "Lua err: " << ident << " requests call, but "
				  << call->ident() << " is still active" << std::endl;
		return 0;
	}

	call = std::make_shared<LuaCall>(L, ident);
	m_lastCall = call;
	return call;
}

std::shared_ptr<LuaCall> LuaSubsystem::startGlobalCall(const std::string &funcName) {
	LuaCall::Ptr call = startCall(funcName);
	if (!call->pushGlobal(funcName))
		return 0;
	return call;
}

std::shared_ptr<LuaCall> LuaSubsystem::startMethodCall(const std::string &className,
		voidPtr instance, const std::string &methodName) {
	LuaCall::Ptr call = startCall(className + "::" + methodName);
	if (!call->pushMethod(className, instance, methodName))
		return 0;
	return call;
}
