#ifndef LUAWRAPPER_H
#define LUAWRAPPER_H

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

class LuaWrapper {
public:
	LuaWrapper();
	virtual ~LuaWrapper();

	bool init();
	void destroy();

	bool loadFile(const char * file);
	bool update();
	void printError(int status);

private:
	lua_State * L;
	Uint32 m_lastTime;
};

#endif /* end of include guard: LUAWRAPPER_H */
