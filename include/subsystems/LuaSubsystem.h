#ifndef LUASUBSYSTEM_H
#define LUASUBSYSTEM_H

#include <memory>
#include "GameEngine.h"
#include "Subsystem.h"

class lua_State;
class LuaCall;

typedef std::shared_ptr<void> voidPtr;

class LuaSubsystem : public Subsystem {
public:
	LuaSubsystem(GameEngine *engine);
	virtual ~LuaSubsystem();

	bool init();
	void update();
	void destroy();

	bool loadFile(const std::string &file);
	void printError(int status) const;


	std::shared_ptr<LuaCall> startCall(const std::string &ident);
	std::shared_ptr<LuaCall> startGlobalCall(const std::string &funcName);
	std::shared_ptr<LuaCall> startEventCall(const std::string &funcName);
	std::shared_ptr<LuaCall> startMethodCall(const std::string &className,
			voidPtr instance, const std::string &methodName);

private:
	lua_State *L;
	int m_lastTime;

	int m_callArgs;
	std::weak_ptr<LuaCall> m_lastCall;
};

#endif /* end of include guard: LUASUBSYSTEM_H*/
