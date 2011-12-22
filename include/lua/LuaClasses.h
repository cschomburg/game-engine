#ifndef LUACLASSES_H
#define LUACLASSES_H

#include "LuaClass.h"

extern LuaClass luaBody;
extern LuaClass luaComponent;
extern LuaClass luaGameEngine;
extern LuaClass luaObject;
extern LuaClass luaRenderable;

void LuaBody_classSetup(lua_State *L);
void LuaComponent_classSetup(lua_State *L);
void LuaGameEngine_classSetup(lua_State *L);
void LuaObject_classSetup(lua_State *L);
void LuaRenderable_classSetup(lua_State *L);

#endif /* end of include guard: LUACLASSES_H */
