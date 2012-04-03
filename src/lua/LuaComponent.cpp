#include <string>
#include "Component.h"
#include "lua/LuaClasses.h"

LuaClass luaComponent("Component");

int LuaComponent_objectID(lua_State *L) {
	Component::Ptr component = luaComponent.check<Component>(L, 1);
	lua_pop(L, 1);

	lua_pushstring(L, component->objectID().c_str());
	return 1;
}

int LuaComponent_setObjectID(lua_State *L) {
	Component::Ptr component = luaComponent.check<Component>(L, 1);
	component->setObjectID(std::string(luaL_checkstring(L, 2)));
	lua_pop(L, 1);
	return 0;
}

void LuaComponent_classSetup(lua_State *L) {
	static const luaL_Reg methods[] = {
		{ "objectID", LuaComponent_objectID },
		{ "setObjectID", LuaComponent_setObjectID },
		{ 0, 0 },
	};

	static const luaL_Reg meta[] = {
		{ 0, 0 },
	};

	luaComponent.registerClass(L, methods, meta);
}
