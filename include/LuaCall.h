#ifndef LUACALL_H
#define LUACALL_H

#include <memory>
#include <string>

class lua_State;

typedef std::shared_ptr<void> voidPtr;

class LuaCall {
public:
	typedef std::shared_ptr<LuaCall> Ptr;

	LuaCall(lua_State *L, const std::string &ident);
	virtual ~LuaCall();

	std::string ident() const;

	bool pushGlobal(const std::string &name);

	void push(const std::string &value);
	void push(int number);
	void push(double number);
	void push(bool boolean);
	bool push(const std::string &className, voidPtr instance);

	bool pushMethod(const std::string &className, voidPtr instance, const std::string &methodName);

	bool execute();

private:
	std::string m_ident;
	lua_State *L;
	int m_numStack;
};

#endif /* end of include guard: LUACALL_H */
