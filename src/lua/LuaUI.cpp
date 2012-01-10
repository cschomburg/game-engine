#include "GameEngine.h"
#include "lua/LuaClasses.h"
#include "subsystems/UISubsystem.h"

LuaClass luaUI("UI");

int LuaUI_root(lua_State *L) {
	luaWidget.push(L, GameEngine::instance()->ui()->rootWidget());
	return 1;
}

void LuaUI_classSetup(lua_State *L) {
	static const luaL_Reg methods[] = {
		{ "root", LuaUI_root },
		{ 0, 0 },
	};

	static const luaL_Reg meta[] = {
		{ 0, 0 },
	};

	luaUI.registerClass(L, methods, meta);
}
