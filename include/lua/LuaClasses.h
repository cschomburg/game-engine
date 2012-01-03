#ifndef LUACLASSES_H
#define LUACLASSES_H

#include "LuaClass.h"

extern LuaClass luaComponent;

extern LuaClass luaBody;
extern LuaClass luaGameEngine;
extern LuaClass luaRenderable;
extern LuaClass luaStaticPos;

void LuaComponent_classSetup(lua_State *L);

void LuaBody_classSetup(lua_State *L);
void LuaGameEngine_classSetup(lua_State *L);
void LuaRenderable_classSetup(lua_State *L);
void LuaStaticPos_classSetup(lua_State *L);

#endif /* end of include guard: LUACLASSES_H */
