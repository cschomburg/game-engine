#ifndef LUACLASSES_H
#define LUACLASSES_H

#include "LuaClass.h"

extern LuaClass luaGameEngine;
extern LuaClass luaGraphics;

extern LuaClass luaComponent;
extern LuaClass luaBody;
extern LuaClass luaFontRenderable;
extern LuaClass luaRenderable;
extern LuaClass luaSolidRenderable;
extern LuaClass luaTextureRenderable;
extern LuaClass luaStaticPos;

void LuaGameEngine_classSetup(lua_State *L);
void LuaGraphics_classSetup(lua_State *L);

void LuaComponent_classSetup(lua_State *L);
void LuaBody_classSetup(lua_State *L);
void LuaFontRenderable_classSetup(lua_State *L);
void LuaRenderable_classSetup(lua_State *L);
void LuaSolidRenderable_classSetup(lua_State *L);
void LuaTextureRenderable_classSetup(lua_State *L);
void LuaStaticPos_classSetup(lua_State *L);

#endif /* end of include guard: LUACLASSES_H */
