#include <string>
#include "lua/LuaComponent.h"
#include "lua/LuaObject.h"
#include "Component.h"

LuaClass luaComponent("Component");

int LuaComponent_type(lua_State *L) {
	Component *component = static_cast<Component *>(luaComponent.check(L, 1));
	lua_pop(L, 1);

	lua_pushstring(L, component->type().c_str());
	return 1;
}

int LuaComponent_object(lua_State *L) {
	Component *component = static_cast<Component *>(luaComponent.check(L, 1));
	lua_pop(L, 1);

	luaObject.push(L, component->object());
	return 1;
}

int LuaComponent_onUpdate(lua_State *L) {
	Component *component = static_cast<Component *>(luaComponent.check(L, 1));
	lua_pop(L, 1);

	component->onUpdate();
	return 0;
}

void LuaComponent_classSetup(lua_State *L) {
	static const luaL_Reg methods[] = {
		{ "type" , LuaComponent_type, },
		{ "object", LuaComponent_object },
		{ "onUpdate", LuaComponent_onUpdate },
		{ 0, 0 },
	};

	static const luaL_Reg meta[] = {
		{ 0, 0 },
	};

	luaComponent.registerClass(L, methods, meta);
}
