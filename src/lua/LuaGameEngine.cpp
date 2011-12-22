#include "Application.h"
#include "GameEngine.h"
#include "Object.h"
#include "lua/LuaClasses.h"

LuaClass luaGameEngine("GameEngine");

int LuaGameEngine_player(lua_State *L) {
	GameEngine *engine = static_cast<GameEngine *>(luaGameEngine.check(L, 1));
	lua_pop(L, 1);

	Object *player = engine->player();
	if (!player) {
		lua_pushnil(L);
	} else {
		luaObject.push(L, player);
	}
	return 1;
}

int LuaGameEngine_setPlayer(lua_State *L) {
	GameEngine *engine = static_cast<GameEngine *>(luaGameEngine.check(L, 1));
	Object *player = static_cast<Object *>(luaObject.check(L, 2));

	engine->setPlayer(player);
	return 0;
}

int LuaGameEngine_registerObject(lua_State *L) {
	GameEngine *engine = static_cast<GameEngine *>(luaGameEngine.check(L, 1));
	Object *object= static_cast<Object *>(luaObject.check(L, 2));

	engine->registerObject(object);
	return 0;
}

int LuaGameEngine_unregisterObject(lua_State *L) {
	GameEngine *engine = static_cast<GameEngine *>(luaGameEngine.check(L, 1));
	Object *object= static_cast<Object *>(luaObject.check(L, 2));

	engine->unregisterObject(object);
	return 0;
}

void LuaGameEngine_classSetup(lua_State *L) {
	static const luaL_Reg methods[] = {
		{ "player", LuaGameEngine_player},
		{ "setPlayer", LuaGameEngine_setPlayer},
		{ "registerObject", LuaGameEngine_registerObject },
		{ "unregisterObject", LuaGameEngine_unregisterObject },
		{ 0, 0 },
	};

	static const luaL_Reg meta[] = {
		{ 0, 0 },
	};

	luaGameEngine.registerClass(L, methods, meta);
}
