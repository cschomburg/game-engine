#include <string>

#include "lua/LuaClasses.h"
#include "subsystems/GraphicsSubsystem.h"

LuaClass luaGraphics("Graphics");

int LuaGraphics_camera(lua_State *L) {
	IPositionable::Ptr positionable = GameEngine::instance()->graphics()->camera();
	if (!positionable) {
		return 0;
	}

	Component::Ptr component = std::dynamic_pointer_cast<Component>(positionable);
	if (!component) {
		return 0;
	}
	LuaClass *luaClass = LuaClass::get(component->type());
	if (!luaClass)
		luaClass = LuaClass::get("Component");
	if (!luaClass)
		return 0;

	luaClass->push(L, component);
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
	IPositionable::Ptr positionable;
	if (lua_gettop(L) != 0 && !lua_isnil(L, 1)) {
		Component::Ptr component = std::static_pointer_cast<Component>(luaComponent.check(L, 1));
		positionable = std::dynamic_pointer_cast<IPositionable>(component);
		if (!positionable) {
			luaL_typerror(L, 1, "IPositionable");
		}
	}
	lua_settop(L, 0);

	GameEngine::instance()->graphics()->setCamera(positionable);
	return 0;
}

int LuaGraphics_viewport(lua_State *L) {
	const Rect &rect = GameEngine::instance()->graphics()->viewport();
	lua_pushnumber(L, rect.bottomLeft().x);
	lua_pushnumber(L, rect.bottomLeft().y);
	lua_pushnumber(L, rect.w);
	lua_pushnumber(L, rect.h);
	return 4;
}

void LuaGraphics_classSetup(lua_State *L) {
	static const luaL_Reg methods[] = {
		{ "camera", LuaGraphics_camera },
		{ "setCamera", LuaGraphics_setCamera },
		{ "scale", LuaGraphics_scale },
		{ "setScale", LuaGraphics_setScale },
		{ "viewport", LuaGraphics_viewport },
		{ 0, 0 },
	};

	static const luaL_Reg meta[] = {
		{ 0, 0 },
	};

	luaGraphics.registerClass(L, methods, meta);
}
