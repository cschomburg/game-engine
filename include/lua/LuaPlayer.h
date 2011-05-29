#ifndef LUAPLAYER_H
#define LUAPLAYER_H

#include "lua/luna.h"
#include "Player.h"

class LuaPlayer : public Player {
public:
	LuaPlayer(lua_State * L, bool internal);
	virtual ~LuaPlayer();

	int setVelocity(lua_State * L);
public:

	static const char * className;
	static const Luna<LuaPlayer>::FunctionType Functions[];
	static const Luna<LuaPlayer>::PropertyType Properties[];
	bool isExisting;
	bool isPrecious;
};

#endif /* end of include guard: LUAPLAYER_H */
