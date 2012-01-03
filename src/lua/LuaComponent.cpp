#include <string>
#include "Component.h"
#include "lua/LuaClasses.h"

LuaClass luaComponent("Component");

int LuaComponent_type(lua_State *L) {
	Component::Ptr component = luaComponent.check<Component>(L, 1);
	lua_pop(L, 1);

	lua_pushstring(L, component->type().c_str());
	return 1;
}

int LuaComponent_objectID(lua_State *L) {
	Component::Ptr component = luaComponent.check<Component>(L, 1);
	lua_pop(L, 1);

	lua_pushstring(L, component->objectID().c_str());
	return 1;
}

void LuaComponent_classSetup(lua_State *L) {
	static const luaL_Reg methods[] = {
		{ "type" , LuaComponent_type, },
		{ "objectID", LuaComponent_objectID },
		{ 0, 0 },
	};

	static const luaL_Reg meta[] = {
		{ 0, 0 },
	};

	luaComponent.registerClass(L, methods, meta);
}
