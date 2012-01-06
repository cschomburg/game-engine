#include <cstring>
#include <string>

#include "GameEngine.h"
#include "components/Renderable.h"
#include "interfaces/IPositionable.h"
#include "subsystems/GraphicsSubsystem.h"
#include "lua/LuaClasses.h"

LuaClass luaRenderable("Renderable", &luaComponent);

int LuaRenderable_new(lua_State *L) {
	std::string name(luaL_checkstring(L, 1));
	lua_pop(L, 1);

	luaRenderable.push(L, Renderable::Ptr(new Renderable(name)));
	return 1;
}

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

// TODO: Cleaner gradient API
int LuaRenderable_gradient(lua_State *L) {
	Renderable::Ptr renderable = std::static_pointer_cast<Renderable>(luaRenderable.check(L, 1));
	lua_pop(L, 1);

	Gradient gradient = renderable->gradient();
	lua_pushnumber(L, gradient.first.r);
	lua_pushnumber(L, gradient.first.g);
	lua_pushnumber(L, gradient.first.b);
	lua_pushnumber(L, gradient.first.a);
	lua_pushnumber(L, gradient.second.r);
	lua_pushnumber(L, gradient.second.g);
	lua_pushnumber(L, gradient.second.b);
	lua_pushnumber(L, gradient.second.a);
	return 8;
}

int LuaRenderable_setGradient(lua_State *L) {
	Renderable::Ptr renderable = std::static_pointer_cast<Renderable>(luaRenderable.check(L, 1));
	float aR = luaL_checknumber(L, 2);
	float aG = luaL_checknumber(L, 3);
	float aB = luaL_checknumber(L, 4);
	float aA = luaL_checknumber(L, 5);
	float bR = luaL_checknumber(L, 6);
	float bG = luaL_checknumber(L, 7);
	float bB = luaL_checknumber(L, 8);
	float bA = luaL_checknumber(L, 9);
	lua_pop(L, 9);

	renderable->setGradient(Gradient(Color(aR, aG, aB, aA), Color(bR, bG, bB, bA)));
	return 0;
}

int LuaRenderable_setTexture(lua_State *L) {
	Renderable::Ptr renderable = std::static_pointer_cast<Renderable>(luaRenderable.check(L, 1));
	const char *texturePath = luaL_checkstring(L, 2);
	lua_pop(L, 2);

	renderable->setTexture(texturePath);
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

int LuaRenderable_setShape(lua_State *L) {
	Renderable::Ptr renderable = std::static_pointer_cast<Renderable>(luaRenderable.check(L, 1));
	const char *type = luaL_checkstring(L, 2);

	if (strcmp(type, "box") == 0) {
		float width = luaL_checknumber(L, 3);
		float height = luaL_checknumber(L, 4);
		lua_pop(L, 4);

		renderable->setShape(Convex::fromSize(Vector2(width, height)));
		return 0;
	}

	lua_pop(L, 2);
	return 0;
}

void LuaRenderable_classSetup(lua_State *L) {
	static const luaL_Reg methods[] = {
		{ "new", LuaRenderable_new },
		{ "register", LuaRenderable_register },
		{ "unregister", LuaRenderable_unregister },
		{ "positionable", LuaRenderable_positionable },
		{ "setPositionable", LuaRenderable_setPositionable },
		{ "color", LuaRenderable_color },
		{ "setColor", LuaRenderable_setColor },
		{ "gradient", LuaRenderable_gradient },
		{ "setGradient", LuaRenderable_setGradient },
		{ "setTexture", LuaRenderable_setTexture },
		{ "zIndex", LuaRenderable_zIndex },
		{ "setZIndex", LuaRenderable_setZIndex },
		{ "parallax", LuaRenderable_parallax},
		{ "setParallax", LuaRenderable_setParallax },
		{ "blendMode", LuaRenderable_blendMode},
		{ "setBlendMode", LuaRenderable_setBlendMode },
		{ "setShape", LuaRenderable_setShape },
		{ 0, 0 },
	};

	static const luaL_Reg meta[] = {
		{ 0, 0 },
	};

	luaRenderable.registerClass(L, methods, meta);
}
