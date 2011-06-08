#ifndef LUAOBJECT_H
#define LUAOBJECT_H

#include "lua/luna.h"

class LuaObject {
public:
	LuaObject();
	LuaObject(lua_State * L, bool internal);
	virtual ~LuaObject();

public:
	static const char * className;
	static const Luna<LuaObject>::FunctionType Functions[];
	static const Luna<LuaObject>::PropertyType Properties[];
	bool isExisting;
	bool isPrecious;
};

#endif /* end of include guard: LUAOBJECT_H */
