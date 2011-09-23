#ifndef LUASUBSYSTEM_H
#define LUASUBSYSTEM_H

#include "Subsystem.h"

class lua_State;

class LuaSubsystem : public Subsystem {
public:
	LuaSubsystem(GameEngine *engine);
	virtual ~LuaSubsystem();

	bool init();
	void update();
	void destroy();

	lua_State *state() const;

	bool loadFile(const std::string &file);
	void printError(int status) const;

	void push(const std::string &className, void *instance, const char *field);

private:
	lua_State *L;
	int m_lastTime;
};

#endif /* end of include guard: LUASUBSYSTEM_H*/
