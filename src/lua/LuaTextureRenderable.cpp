#include "components/TextureRenderable.h"
#include "lua/LuaClasses.h"

LuaClass luaTextureRenderable("TextureRenderable", &luaRenderable);

int LuaTextureRenderable_new(lua_State *L) {
	luaTextureRenderable.push(L, std::make_shared<TextureRenderable>());
	return 1;
}

int LuaTextureRenderable_setTexture(lua_State *L) {
	TextureRenderable::Ptr renderable = luaTextureRenderable.check<TextureRenderable>(L, 1);
	renderable->setTexture(std::string(luaL_checkstring(L, 2)));
	lua_pushboolean(L, renderable->texture() != 0);
	return 1;
}

void LuaTextureRenderable_classSetup(lua_State *L) {
	static const luaL_Reg methods[] = {
		{ "new", LuaTextureRenderable_new },
		{ "setTexture", LuaTextureRenderable_setTexture },
		{ 0, 0 },
	};

	static const luaL_Reg meta[] = {
		{ 0, 0 },
	};

	luaTextureRenderable.registerClass(L, methods, meta);
}
