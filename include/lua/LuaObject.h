#ifndef LUAOBJECT_H
#define LUAOBJECT_H

#include "lua/LuaClass.h"

extern LuaClass luaObject;

void LuaObject_classSetup(lua_State *L);

#endif /* end of include guard: LUAOBJECT_H */
