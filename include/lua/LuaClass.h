#ifndef LUACLASS_H
#define LUACLASS_H

#include <string>

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

class LuaClass {
public:
	LuaClass(const std::string &name);
	virtual ~LuaClass();

	std::string name() const;

	void registerClass(lua_State *L, const luaL_Reg methods[], const luaL_Reg meta[]);
	void *check(lua_State *L, int index);
	int push(lua_State *L, void *instance);

private:
	std::string m_name;
};

#endif /* end of include guard: LUACLASS_H */
