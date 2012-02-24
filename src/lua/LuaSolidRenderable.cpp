#include "components/SolidRenderable.h"
#include "lua/LuaClasses.h"

LuaClass luaSolidRenderable("SolidRenderable", &luaRenderable);

int LuaSolidRenderable_new(lua_State *L) {
	luaSolidRenderable.push(L, std::make_shared<SolidRenderable>());
	return 1;
}

void LuaSolidRenderable_classSetup(lua_State *L) {
	static const luaL_Reg methods[] = {
		{ "new", LuaSolidRenderable_new },
		{ 0, 0 },
	};

	static const luaL_Reg meta[] = {
		{ 0, 0 },
	};

	luaSolidRenderable.registerClass(L, methods, meta);
}
