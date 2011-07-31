#ifndef LUAWRAPPER_H
#define LUAWRAPPER_H

class lua_State;

class LuaWrapper {
public:
	LuaWrapper();
	virtual ~LuaWrapper();

	bool init();
	void destroy();
	lua_State *state() const;

	bool loadFile(const std::string &file);
	bool update();
	void printError(int status) const;

	void push(const std::string &className, void *instance, const char *field);

private:
	lua_State *L;
	Uint32 m_lastTime;
};

#endif /* end of include guard: LUAWRAPPER_H */
