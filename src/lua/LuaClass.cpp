#include <iostream>
#include "lua/LuaClass.h"

std::map<std::string, LuaClass *> LuaClass::m_classes;

LuaClass::LuaClass(const std::string &name, LuaClass *parent) {
	m_name = name;
	m_parent = parent;
}

LuaClass::~LuaClass() {}

std::string LuaClass::name() const {
	return m_name;
}

LuaClass *LuaClass::parent() const {
	return m_parent;
}

bool LuaClass::isDescendant(lua_State *L, int index) {
	if (!lua_istable(L, index))
		return false;

	luaL_getmetatable(L, m_name.c_str()); // Fetch class metatable
	lua_pushvalue(L, index); // Dup instance table
	while (lua_getmetatable(L, -1)) { // getmetatable(table)
		lua_remove(L, -2); // Remove table
		if (lua_rawequal(L, -1, -2)) { // metatable == class metatable?
			lua_pop(L, 2); // Pop metatable and class metatable 
			return true;
		}
		lua_pushliteral(L, "__index");
		lua_rawget(L, -2); // metatable['__index'] => table
		lua_remove(L, -2); // Remove metatable
	}

	lua_pop(L, 2); // Pop last table and metatable
	return false;
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

	lua_pop(L, 1); // Drop metatable

	if (m_parent) { // Inherit methods from parent table
		luaL_getmetatable(L, m_parent->name().c_str()); // Get parent metatable from registry
		lua_setmetatable(L, -2); // setmetatable(methods, parents_metatable)
	}

	lua_pop(L, 1); // Drop methods table
	m_classes[m_name] = this;
}

void *LuaClass::check(lua_State *L, int index) {
	if (!isDescendant(L, index)) {
		luaL_typerror(L, index, m_name.c_str());
		return 0;
	}

	lua_pushnumber(L, 0);
	lua_rawget(L, index); // Fetch userdata of object-table
	void *instance = lua_touserdata(L, -1);
	lua_pop(L, 1); // Pop userdata

	return instance;
}

int LuaClass::push(lua_State *L, void *instance) {
	if (!instance) {
		lua_pushnil(L);
		return 1;
	}

	// Query registry for existing instance table
	lua_pushlightuserdata(L, instance); // Push instance pointer
	lua_rawget(L, LUA_REGISTRYINDEX); // Query registry for instance table
	if (!lua_isnil(L, -1)) // Return existing table
		return 1;
	lua_pop(L, 1); // Pop nil

	// Create new instance table ...
	lua_newtable(L); // Push new table for instance

	luaL_getmetatable(L, m_name.c_str()); // Push class metatable from registry
	lua_setmetatable(L, -2); // setmetatable(table, metatable)

	lua_pushnumber(L, 0);
	lua_pushlightuserdata(L, instance);
	lua_rawset(L, -3); // table[0] = userdata

	// ... and store in registry
	lua_pushlightuserdata(L, instance); // Push instance pointer
	lua_pushvalue(L, -2); // Dup instance table
	lua_rawset(L, LUA_REGISTRYINDEX);

	// Return instance table
	return 1;
}

LuaClass *LuaClass::get(const std::string &name) {
	return m_classes.find(name)->second;
}
