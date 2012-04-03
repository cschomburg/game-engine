#include <iostream>
#include "LuaClass.h"

std::map<std::string, LuaClass *> LuaClass::m_classes;
std::map<void *, voidPtr> LuaClass::m_managedInstances;

static int Userdata_gc(lua_State *L) {
	void **instance = static_cast<void **>(lua_touserdata(L, -1));
	LuaClass::remove(*instance);
	return 0;
}

const luaL_reg LuaClass::userdataMeta[] = {
	{ "__gc", Userdata_gc },
	{ 0, 0 },
};

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

int LuaClass::setupUserdataMeta(lua_State *L) {
	luaL_register(L, "LuaClassInstance", userdataMeta);
	return 1;
}

/**
 * Checks if the variable on the stack is a subclass of this class by
 * comparing its metatable tree with the class metatable.
 */
bool LuaClass::isDescendant(lua_State *L, int index) {
	if (!lua_istable(L, index))
		return false;

	lua_pushstring(L, m_name.c_str());
	lua_rawget(L, LUA_REGISTRYINDEX); // hidden = registry[class]

	lua_pushliteral(L, "meta");
	lua_rawget(L, -2); // metatable = hidden[class]

	lua_pushvalue(L, index); // table = instance
	while (lua_getmetatable(L, -1)) { // getmetatable(table)
		lua_remove(L, -2); // Remove table
		if (lua_rawequal(L, -1, -2)) { // metatable == class metatable?
			lua_pop(L, 3); // Pop metatable and class metatable and hidden
			return true;
		}
		lua_pushliteral(L, "__index");
		lua_rawget(L, -2); // table = metatable['__index']
		lua_remove(L, -2); // Remove metatable
	}

	lua_pop(L, 3); // Pop last table, metatable and hidden
	return false;
}

/**
 * Registers a LuaClass in the current Lua environment.
 * The table containing all methods is globally available under the class name,
 * the metatable for instances of this class is stored in the registry under
 * the class name.
 * The Superclasses' instance table will be set as the metatable for the
 * methods table.
 */
void LuaClass::registerClass(lua_State *L, const luaL_Reg methods[], const luaL_Reg meta[]) {
	const char *name = m_name.c_str();
	luaL_register(L, name, methods); // Create methods table in globals
	// [methods]

	lua_pushliteral(L, "type");
	lua_pushstring(L, name);
	lua_rawset(L, -3); // methods.type = className
	// [methods]

	lua_newtable(L); // hidden class information
	// [methods, hidden]

	lua_pushliteral(L, "hidden");
	lua_pushvalue(L, -2);
	lua_rawset(L, -4);

	lua_newtable(L); // Create new table for metamethods
	luaL_register(L, 0, meta); // Populate metatable
	// [methods, hidden, metatable]

	lua_pushliteral(L, "__index");
	lua_pushvalue(L, -4); // Dup methods table
	lua_rawset(L, -3); // metatable.__index = methods
	// [methods, hidden. metatable]

	lua_pushliteral(L, "meta");
	lua_pushvalue(L, -2); // Dup metatable
	lua_rawset(L, -4); // hidden.meta = metatable
	lua_pop(L, 1); // Drop metatable
	// [methods, hidden]

	lua_newtable(L); // instances
	lua_pushliteral(L, "instances");
	lua_pushvalue(L, -2); // Dup instances
	lua_rawset(L, -4); // hidden.instances = {}
	// [methods, hidden, instances]

	lua_newtable(L); // instances meta
	lua_pushliteral(L, "__mode");
	lua_pushliteral(L, "v");
	lua_rawset(L, -3); // meta.__mode = "v"
	lua_setmetatable(L, -2); // setmetatable(instances, meta)
	lua_pop(L, 1); // Drop instances
	// [methods, hidden]

	lua_pushstring(L, name);
	lua_pushvalue(L, -2); // Dup hidden
	lua_rawset(L, LUA_REGISTRYINDEX); // registry[class] = hidden
	// [methods, hidden]

	lua_pop(L, 1); // Drop hidden table
	// [methods]

	if (m_parent) { // Inherit methods from parent table
		lua_pushstring(L, m_parent->name().c_str());
		lua_rawget(L, LUA_REGISTRYINDEX); // hidden = registry[class]
		// [methods, hidden]
		lua_pushliteral(L, "meta");
		lua_rawget(L, -2); // metatable = hidden.meta
		// [methods, hidden, metatable]
		lua_setmetatable(L, -3); // setmetatable(methods, parents_metatable)
		lua_pop(L, 1); // Drop hidden table
		// [methods]
	}

	lua_pop(L, 1); // Drop methods table
	m_classes[m_name] = this;
}

void *LuaClass::checkRaw(lua_State *L, int index) {
	if (!isDescendant(L, index)) {
		luaL_typerror(L, index, m_name.c_str());
		return 0;
	}

	lua_pushnumber(L, 0);
	lua_rawget(L, index); // Fetch userdata of object-table
	void **instance = static_cast<void **>(lua_touserdata(L, -1));
	lua_pop(L, 1); // Pop userdata

	return *instance;
}

voidPtr LuaClass::check(lua_State *L, int index) {
	void *instance = checkRaw(L, index);
	if (!instance) {
		luaL_typerror(L, index, m_name.c_str());
	}

	auto it = m_managedInstances.find(instance);
	if (it == m_managedInstances.end()) {
		luaL_argerror(L, index, "invalid instance");
	}

	return it->second;
}

bool LuaClass::pushRaw(lua_State *L, void *instance, bool noCreate) {
	if (!instance) {
		lua_pushnil(L);
		return false;
	}

	// Query registry for existing instance table
	lua_pushstring(L, m_name.c_str());
	lua_rawget(L, LUA_REGISTRYINDEX); // hidden = registry[class]
	// [hidden]

	lua_pushliteral(L, "instances");
	lua_rawget(L, -2); // instances = hidden.instances
	// [hidden, instances]

	lua_pushlightuserdata(L, instance); // Push raw instance pointer
	lua_rawget(L, -2); // instance = instances[raw]
	if (noCreate || !lua_isnil(L, -1)) { // instance != nil
		lua_remove(L, -2); // Drop instances table
		lua_remove(L, -2); // Drop hidden table
		return !lua_isnil(L, -1); // [instance]
	}
	lua_pop(L, 1); // Pop nil
	// [hidden, instances]

	lua_newtable(L); // Push new table for instance
	// [hidden, instances, instance]

	lua_pushliteral(L, "meta");
	lua_rawget(L, -4); // metatable = hidden.meta
	lua_setmetatable(L, -2); // setmetatable(instance, metatable)
	// [hidden, instances, instance]

	void **udata = static_cast<void **>(lua_newuserdata(L, sizeof(void*)));
	*udata = instance;
	lua_pushnumber(L, 0);
	lua_pushvalue(L, -2); // Dup userdata
	lua_rawset(L, -4); // instance[0] = userdata
	// [hidden, instances, instance, userdata]

	luaL_getmetatable(L, "LuaClassInstance");
	if (lua_isnil(L, -1)) {
		lua_pop(L, 1); // Drop nil
		setupUserdataMeta(L);
	}
	lua_setmetatable(L, -2); // setmetatable(userdata, instanceMeta)
	lua_pop(L, 1); // Drop userdata
	// [hidden, instances, instance]

	// ... and store in registry
	lua_pushlightuserdata(L, instance); // Push raw instance pointer
	lua_pushvalue(L, -2); // Dup instance table
	lua_rawset(L, -4); // instances[raw] = instance
	// [hidden, instances, instance]

	lua_remove(L, -2); // Drop instances table
	lua_remove(L, -2); // Drop hidden table

	return true; // [instance]
}

bool LuaClass::push(lua_State *L, voidPtr instance, bool noCreate) {
	if (!instance)
		return false;

	m_managedInstances[instance.get()] = instance;
	return pushRaw(L, instance.get(), noCreate);
}

LuaClass *LuaClass::get(const std::string &name) {
	return m_classes.find(name)->second;
}

void LuaClass::remove(void *instance) {
	auto it = m_managedInstances.find(instance);
	if (it == m_managedInstances.end())
		return;
	m_managedInstances.erase(it);
}
