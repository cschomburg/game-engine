#include <cstring>
#include <string>

#include "GameEngine.h"
#include "Rect.h"

#include "components/Renderable.h"
#include "interfaces/IPositionable.h"
#include "subsystems/GraphicsSubsystem.h"
#include "lua/LuaClasses.h"

LuaClass luaRenderable("Renderable", &luaComponent);

int LuaRenderable_register(lua_State *L) {
	Renderable::Ptr renderable = luaRenderable.check<Renderable>(L, 1);
	lua_pop(L, 1);

	GameEngine::instance()->graphics()->registerRenderable(renderable);
	return 0;
}

int LuaRenderable_unregister(lua_State *L) {
	Renderable::Ptr renderable = luaRenderable.check<Renderable>(L, 1);
	lua_pop(L, 1);

	GameEngine::instance()->graphics()->unregisterRenderable(renderable);
	return 0;
}

int LuaRenderable_positionable(lua_State *L) {
	Renderable::Ptr renderable = luaRenderable.check<Renderable>(L, 1);
	lua_pop(L, 1);

	IPositionable::Ptr positionable = renderable->positionable();
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

int LuaRenderable_setPositionable(lua_State *L) {
	Renderable::Ptr renderable = std::static_pointer_cast<Renderable>(luaRenderable.check(L, 1));
	Component::Ptr component = std::static_pointer_cast<Component>(luaComponent.check(L, 2));
	IPositionable::Ptr positionable = std::dynamic_pointer_cast<IPositionable>(component);
	if (!positionable) {
		luaL_typerror(L, 2, "IPositionable");
	}
	lua_pop(L, 2);

	renderable->setPositionable(positionable);
	return 0;
}

int LuaRenderable_color(lua_State *L) {
	Renderable::Ptr renderable = std::static_pointer_cast<Renderable>(luaRenderable.check(L, 1));
	lua_pop(L, 1);

	Color color = renderable->color();
	lua_pushnumber(L, color.r);
	lua_pushnumber(L, color.g);
	lua_pushnumber(L, color.b);
	lua_pushnumber(L, color.a);
	return 4;
}

int LuaRenderable_setColor(lua_State *L) {
	Renderable::Ptr renderable = std::static_pointer_cast<Renderable>(luaRenderable.check(L, 1));
	float r = luaL_checknumber(L, 2);
	float g = luaL_checknumber(L, 3);
	float b = luaL_checknumber(L, 4);
	float a = luaL_checknumber(L, 5);
	lua_pop(L, 5);

	renderable->setColor(Color(r, g, b, a));
	return 0;
}

int LuaRenderable_zIndex(lua_State *L) {
	Renderable::Ptr renderable = std::static_pointer_cast<Renderable>(luaRenderable.check(L, 1));
	lua_pop(L, 1);

	lua_pushnumber(L, renderable->zIndex());
	return 1;
}

int LuaRenderable_setZIndex(lua_State *L) {
	Renderable::Ptr renderable = std::static_pointer_cast<Renderable>(luaRenderable.check(L, 1));
	float zIndex = luaL_checknumber(L, 2);
	lua_pop(L, 2);

	renderable->setZIndex(zIndex);
	return 0;
}

int LuaRenderable_parallax(lua_State *L) {
	Renderable::Ptr renderable = std::static_pointer_cast<Renderable>(luaRenderable.check(L, 1));
	lua_pop(L, 1);

	lua_pushnumber(L, renderable->parallax().x);
	lua_pushnumber(L, renderable->parallax().y);
	return 2;
}

int LuaRenderable_setParallax(lua_State *L) {
	Renderable::Ptr renderable = std::static_pointer_cast<Renderable>(luaRenderable.check(L, 1));
	float x = luaL_checknumber(L, 2);
	float y = luaL_checknumber(L, 3);
	lua_pop(L, 3);

	renderable->setParallax(Vector2(x, y));
	return 0;
}

int LuaRenderable_drawLayer(lua_State *L) {
	Renderable::Ptr renderable = std::static_pointer_cast<Renderable>(luaRenderable.check(L, 1));
	lua_pop(L, 1);

	switch (renderable->drawLayer()) {
	case DrawLayer::Background: lua_pushstring(L, "background");    break;
	case DrawLayer::World:      lua_pushstring(L, "world");  break;
	case DrawLayer::Foreground: lua_pushstring(L, "foreground"); break;
	default: lua_pushnil(L); break;
	}

	return 1;
}

int LuaRenderable_setDrawLayer(lua_State *L) {
	Renderable::Ptr renderable = std::static_pointer_cast<Renderable>(luaRenderable.check(L, 1));
	const char *modeName = luaL_checkstring(L, 2);
	lua_pop(L, 2);

	DrawLayer layer = DrawLayer::World;
	if (strcmp(modeName, "background") == 0) {
		layer = DrawLayer::Background;
	} else if (strcmp(modeName, "foreground") == 0) {
		layer = DrawLayer::Foreground;
	}

	renderable->setDrawLayer(layer);
	return 0;
}

int LuaRenderable_blendMode(lua_State *L) {
	Renderable::Ptr renderable = std::static_pointer_cast<Renderable>(luaRenderable.check(L, 1));
	lua_pop(L, 1);

	switch (renderable->blendMode()) {
	case BlendMode::Add:    lua_pushstring(L, "add");    break;
	case BlendMode::Blend:  lua_pushstring(L, "blend");  break;
	case BlendMode::Screen: lua_pushstring(L, "screen"); break;
	default: lua_pushnil(L); break;
	}

	return 1;
}

int LuaRenderable_setBlendMode(lua_State *L) {
	Renderable::Ptr renderable = std::static_pointer_cast<Renderable>(luaRenderable.check(L, 1));
	const char *modeName = luaL_checkstring(L, 2);
	lua_pop(L, 2);

	BlendMode mode = BlendMode::Add;
	if (strcmp(modeName, "blend") == 0) {
		mode = BlendMode::Blend;
	} else if (strcmp(modeName, "screen") == 0) {
		mode = BlendMode::Screen;
	}

	renderable->setBlendMode(mode);
	return 0;
}

int LuaRenderable_boundingRect(lua_State *L) {
	Renderable::Ptr renderable = std::static_pointer_cast<Renderable>(luaRenderable.check(L, 1));

	const Rect &rect = renderable->boundingRect();
	lua_pushnumber(L, rect.center().x);
	lua_pushnumber(L, rect.center().y);
	lua_pushnumber(L, rect.size().x);
	lua_pushnumber(L, rect.size().y);
	return 4;
}

int LuaRenderable_setBoundingRect(lua_State *L) {
	Renderable::Ptr renderable = std::static_pointer_cast<Renderable>(luaRenderable.check(L, 1));

	Rect rect;
	if (lua_gettop(L) <= 4) {
		float w = luaL_checknumber(L, 2);
		float h = luaL_checknumber(L, 3);
		rect = Rect(Vector2(), Vector2(w, h), true);//lua_isnil(L, 4));
	} else {
		float x = luaL_checknumber(L, 2);
		float y = luaL_checknumber(L, 3);
		float w = luaL_checknumber(L, 4);
		float h = luaL_checknumber(L, 5);
		rect = Rect(Vector2(x, y), Vector2(w, h), lua_isnil(L, 6));
	}
	renderable->setBoundingRect(rect);

	lua_pop(L, 2);
	return 0;
}

int LuaRenderable_scale(lua_State *L) {
	Renderable::Ptr renderable = std::static_pointer_cast<Renderable>(luaRenderable.check(L, 1));
	lua_pop(L, 1);

	lua_pushnumber(L, renderable->scale());
	return 1;
}

int LuaRenderable_setScale(lua_State *L) {
	Renderable::Ptr renderable = std::static_pointer_cast<Renderable>(luaRenderable.check(L, 1));
	float scale = luaL_checknumber(L, 2);
	lua_pop(L, 2);

	renderable->setScale(scale);
	return 0;
}

void LuaRenderable_classSetup(lua_State *L) {
	static const luaL_Reg methods[] = {
		{ "register", LuaRenderable_register },
		{ "unregister", LuaRenderable_unregister },
		{ "positionable", LuaRenderable_positionable },
		{ "setPositionable", LuaRenderable_setPositionable },
		{ "color", LuaRenderable_color },
		{ "setColor", LuaRenderable_setColor },
		{ "drawLayer", LuaRenderable_drawLayer },
		{ "setDrawLayer", LuaRenderable_setDrawLayer },
		{ "zIndex", LuaRenderable_zIndex },
		{ "setZIndex", LuaRenderable_setZIndex },
		{ "parallax", LuaRenderable_parallax},
		{ "setParallax", LuaRenderable_setParallax },
		{ "blendMode", LuaRenderable_blendMode},
		{ "setBlendMode", LuaRenderable_setBlendMode },
		{ "boundingRect", LuaRenderable_boundingRect },
		{ "setBoundingRect", LuaRenderable_setBoundingRect },
		{ "scale", LuaRenderable_scale },
		{ "setScale", LuaRenderable_setScale },
		{ 0, 0 },
	};

	static const luaL_Reg meta[] = {
		{ 0, 0 },
	};

	luaRenderable.registerClass(L, methods, meta);
}
