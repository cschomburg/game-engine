#include <iostream>
#include "lua/LuaClass.h"


LuaClass::LuaClass(const std::string &name) {
	m_name = name;
}

LuaClass::~LuaClass() {}

std::string LuaClass::name() const {
	return m_name;
}

void LuaClass::registerClass(lua_State *L, const luaL_Reg methods[], const luaL_Reg meta[]) {
	const char *name = m_name.c_str();
	luaL_register(L, name, methods); // Create methods table in globals

	luaL_newmetatable(L, name); // Create metatable for class in registry
	luaL_register(L, 0, meta); // Populate metatable

	lua_pushliteral(L, "class");
	lua_pushstring(L, name);
	lua_rawset(L, -3); // metatable['class'] = className

	lua_pushliteral(L, "__index");
	lua_pushvalue(L, -3); // Dup methods table
	lua_rawset(L, -3); // metatable.__index = methods

	lua_pop(L, 2); // Drop metatable and methods
}

void *LuaClass::check(lua_State *L, int index) {
	const char *name = m_name.c_str();
	luaL_getmetatable(L, name); // Push class metatable from registry
	if (!lua_istable(L, index)
		|| !lua_getmetatable(L, index)
		|| !lua_rawequal(L, -1, -2))
	{
		luaL_typerror(L, index, name);
		return 0;
	}
	lua_pop(L, 2); // Pop metatables

	lua_pushnumber(L, 0);
	lua_rawget(L, index); // Fetch userdata of object-table
	void *instance = lua_touserdata(L, -1);
	lua_pop(L, 1); // Pop userdata

	return instance;
}

void LuaClass::push(lua_State *L, void *instance) {
	if (!instance) {
		lua_pushnil(L);
		return;
	}

	lua_newtable(L); // Push new table

	luaL_getmetatable(L, m_name.c_str()); // Push class metatable from registry
	lua_setmetatable(L, -2); // setmetatable(table, metatable)

	lua_pushnumber(L, 0);
	lua_pushlightuserdata(L, instance);
	lua_rawset(L, -3); // table[0] = userdata
}
