#include <iostream>

#include "Lua.h"
#include "LuaCall.h"
#include "LuaClass.h"

LuaCall::LuaCall(lua_State *L, const std::string &ident) {
	m_numStack = 0;
	m_ident = ident;
	this->L = L;

	int num = lua_gettop(L);
	if (num > 0) {
		std::cout << "Lua warn (" << m_ident << "::begin): stack is not empty ("
				  << num << " values)" << std::endl;
	}
}

LuaCall::~LuaCall() {
	if (m_numStack > 0) {
		lua_pop(L, m_numStack);
	}
	int num = lua_gettop(L);
	if (num > 0) {
		std::cout << "Lua warn (" << m_ident << "::end): stack is not empty ("
				  << num << " values)" << std::endl;
	}
}

std::string LuaCall::ident() const {
	return m_ident;
}

bool LuaCall::pushGlobal(const std::string &name) {
	m_numStack++;
	lua_getfield(L, LUA_GLOBALSINDEX, name.c_str());
	return lua_isnil(L, -1) == 0;
}

void LuaCall::push(const std::string &text) {
	m_numStack++;
	lua_pushstring(L, text.c_str());
}

void LuaCall::push(int number) {
	push(static_cast<float>(number));
}

void LuaCall::push(double number) {
	m_numStack++;
	lua_pushnumber(L, number);
}

void LuaCall::push(bool boolean) {
	m_numStack++;
	lua_pushboolean(L, boolean);
}

bool LuaCall::push(const std::string &className, voidPtr instance) {
	m_numStack++;
	LuaClass *luaClass = LuaClass::get(className);
	if (!luaClass) {
		lua_pushnil(L);
		return false;
	}
	luaClass->push(L, instance);
	return true;
}

bool LuaCall::pushMethod(const std::string &className, voidPtr instance, const std::string &methodName) {
	push(className, instance); // [instance]
	lua_pushstring(L, methodName.c_str()); // [instance,methodName]
	lua_gettable(L, -2); // [instance,method]
	lua_pushvalue(L, -2); // [instance,method,instance]
	lua_remove(L, -3); // [method,instance]
	m_numStack += 1;
	return lua_isfunction(L, -2) == 1;
}

bool LuaCall::execute() {
	if (m_numStack <= 0)
		return false;
	int status = lua_pcall(L, m_numStack-1, 0, 0);
	m_numStack = 0;
	if (status != 0) {
		std::cout << "Lua err (" << m_ident << "::call): "<< lua_tostring(L, -1) << std::endl;
		lua_pop(L, 1);
		return false;
	}
	return true;
}
