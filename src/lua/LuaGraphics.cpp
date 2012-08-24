#include <string>

#include "lua/LuaClasses.h"
#include "subsystems/GraphicsSubsystem.h"

LuaClass luaGraphics("Graphics");

int LuaGraphics_camera(lua_State *L) {
	Positionable::Ptr positionable = GameEngine::instance()->graphics()->camera();
	if (!positionable) {
		return 0;
	}

	luaPositionable.push(L, positionable);
	return 1;
}

int LuaGraphics_scale(lua_State *L) {
	lua_pushnumber(L, GameEngine::instance()->graphics()->scale());
	return 1;
}

int LuaGraphics_setScale(lua_State *L) {
	GameEngine::instance()->graphics()->setScale(luaL_checknumber(L, 1));
	lua_pop(L, 1);
	return 0;
}

int LuaGraphics_setCamera(lua_State *L) {
	Positionable::Ptr positionable = 0;
	if (lua_gettop(L) != 0 && !lua_isnil(L, 1)) {
		positionable = luaPositionable.check<Positionable>(L, 1);
	}
	lua_settop(L, 0);

	GameEngine::instance()->graphics()->setCamera(positionable);
	return 0;
}

int LuaGraphics_viewport(lua_State *L) {
	const Rect &rect = GameEngine::instance()->graphics()->viewport();
	lua_pushnumber(L, rect.pos(Anchor::center).x);
	lua_pushnumber(L, rect.pos(Anchor::center).y);
	lua_pushnumber(L, rect.size().x);
	lua_pushnumber(L, rect.size().y);
	return 4;
}

int LuaGraphics_toWorldPos(lua_State *L) {
	float x = luaL_checknumber(L, 1);
	float y = luaL_checknumber(L, 2);
	Vector2 pos = GameEngine::instance()->graphics()->toWorldPos(Vector2(x, y), Anchor::topLeft);
	lua_pushnumber(L, pos.x);
	lua_pushnumber(L, pos.y);
	return 2;
}

void LuaGraphics_classSetup(lua_State *L) {
	static const luaL_Reg methods[] = {
		{ "camera", LuaGraphics_camera },
		{ "setCamera", LuaGraphics_setCamera },
		{ "scale", LuaGraphics_scale },
		{ "setScale", LuaGraphics_setScale },
		{ "viewport", LuaGraphics_viewport },
		{ "toWorldPos", LuaGraphics_toWorldPos },
		{ 0, 0 },
	};

	static const luaL_Reg meta[] = {
		{ 0, 0 },
	};

	luaGraphics.registerClass(L, methods, meta);
}
