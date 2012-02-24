#include "components/FontRenderable.h"
#include "lua/LuaClasses.h"

LuaClass luaFontRenderable("FontRenderable", &luaRenderable);

int LuaFontRenderable_new(lua_State *L) {
	luaFontRenderable.push(L, std::make_shared<FontRenderable>());
	return 1;
}

int LuaFontRenderable_setFont(lua_State *L) {
	FontRenderable::Ptr renderable = luaFontRenderable.check<FontRenderable>(L, 1);
	std::string fontPath = std::string(luaL_checkstring(L, 2));
	int size = luaL_checkint(L, 3);
	renderable->setFont(fontPath, size);
	lua_pushboolean(L, renderable->font() != 0);
	return 1;
}

int LuaFontRenderable_text(lua_State *L) {
	FontRenderable::Ptr renderable = luaFontRenderable.check<FontRenderable>(L, 1);
	lua_pushstring(L, renderable->text().c_str());
	return 1;
}

int LuaFontRenderable_setText(lua_State *L) {
	FontRenderable::Ptr renderable = luaFontRenderable.check<FontRenderable>(L, 1);
	renderable->setText(std::string(luaL_checkstring(L, 2)));
	return 0;
}

void LuaFontRenderable_classSetup(lua_State *L) {
	static const luaL_Reg methods[] = {
		{ "new", LuaFontRenderable_new },
		{ "setFont", LuaFontRenderable_setFont },
		{ "text", LuaFontRenderable_setText },
		{ "setText", LuaFontRenderable_setText },
		{ 0, 0 },
	};

	static const luaL_Reg meta[] = {
		{ 0, 0 },
	};

	luaFontRenderable.registerClass(L, methods, meta);
}
