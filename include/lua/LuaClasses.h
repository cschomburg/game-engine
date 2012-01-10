#ifndef LUACLASSES_H
#define LUACLASSES_H

#include "LuaClass.h"

extern LuaClass luaGameEngine;
extern LuaClass luaUI;

extern LuaClass luaComponent;
extern LuaClass luaBody;
extern LuaClass luaGraphics;
extern LuaClass luaRenderable;
extern LuaClass luaStaticPos;

extern LuaClass luaWidget;
extern LuaClass luaSolidWidget;
extern LuaClass luaTextWidget;

void LuaGameEngine_classSetup(lua_State *L);
void LuaUI_classSetup(lua_State *L);

void LuaComponent_classSetup(lua_State *L);
void LuaBody_classSetup(lua_State *L);
void LuaGraphics_classSetup(lua_State *L);
void LuaRenderable_classSetup(lua_State *L);
void LuaStaticPos_classSetup(lua_State *L);

void LuaWidget_classSetup(lua_State *L);
void LuaSolidWidget_classSetup(lua_State *L);
void LuaTextWidget_classSetup(lua_State *L);

#endif /* end of include guard: LUACLASSES_H */
