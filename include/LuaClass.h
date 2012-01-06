#ifndef LUACLASS_H
#define LUACLASS_H

#include <map>
#include <memory>
#include <string>

#include "Lua.h"

typedef std::shared_ptr<void> voidPtr;

class LuaClass {
public:
	LuaClass(const std::string &name, LuaClass *parent = 0);
	virtual ~LuaClass();

	std::string name() const;
	LuaClass *parent() const;

	bool isDescendant(lua_State *L, int index);
	void registerClass(lua_State *L, const luaL_Reg methods[], const luaL_Reg meta[]);
	void *checkRaw(lua_State *L, int index);
	voidPtr check(lua_State *L, int index);
	int pushRaw(lua_State *L, void *instance);
	int push(lua_State *L, voidPtr instance);

	template<typename T> typename T::Ptr check(lua_State *L, int index) {
		return std::static_pointer_cast<T>(check(L, index));
	}

	static LuaClass *get(const std::string &name);
	static void remove(void *instance);

private:
	static int setupUserdataMeta(lua_State *L);

private:
	std::string m_name;
	LuaClass *m_parent;
	static std::map<void *, voidPtr> m_managedInstances;
	static std::map<std::string, LuaClass *> m_classes;
	static const luaL_reg userdataMeta[];
};

#endif /* end of include guard: LUACLASS_H */
