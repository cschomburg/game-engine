#ifndef LUAWRAPPER_H
#define LUAWRAPPER_H

#include <map>

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

#include "lua/LuaEntity.h"

class LuaWrapper {
public:
	LuaWrapper();
	virtual ~LuaWrapper();

	bool init();
	void destroy();
	lua_State * state() const;

	bool loadFile(const char * file);
	bool update();
	void printError(int status);

	template<class T, class S> void push(T * object, const char * name);
	void push(Entity * entity, const char * name);

private:
	lua_State * L;
	Uint32 m_lastTime;
	std::map<void *, LuaObject *> m_objects;
};

#endif /* end of include guard: LUAWRAPPER_H */
