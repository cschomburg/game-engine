#ifndef LUACLASS_H
#define LUACLASS_H

#include <map>
#include <string>

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

class LuaClass {
public:
	LuaClass(const std::string &name, LuaClass *parent = 0);
	virtual ~LuaClass();

	std::string name() const;
	LuaClass *parent() const;

	bool isDescendant(lua_State *L, int index);
	void registerClass(lua_State *L, const luaL_Reg methods[], const luaL_Reg meta[]);
	void *check(lua_State *L, int index);
	int push(lua_State *L, void *instance);

	static LuaClass *get(const std::string &name);

private:
	std::string m_name;
	LuaClass *m_parent;
	static std::map<std::string, LuaClass *> m_classes;
};

#endif /* end of include guard: LUACLASS_H */
