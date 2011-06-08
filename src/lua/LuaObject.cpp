#include "lua/LuaObject.h"

const char * LuaObject::className = "Object";
const Luna<LuaObject>::FunctionType LuaObject::Functions[] = {{0}};
const Luna<LuaObject>::PropertyType LuaObject::Properties[] = {{0}};

LuaObject::LuaObject() {};

LuaObject::LuaObject(lua_State * L, bool internal) {};

LuaObject::~LuaObject() {};
