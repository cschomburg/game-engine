#ifndef LUAPLAYER_H
#define LUAPLAYER_H

#include "lua/LuaEntity.h"
#include "Player.h"

class LuaPlayer : public LuaEntity {
public:
	LuaPlayer(lua_State * L, bool internal);
	LuaPlayer(Player * player);
	virtual ~LuaPlayer();

public:
	static const char * className;
	static const Luna<LuaPlayer>::FunctionType Functions[];
	static const Luna<LuaPlayer>::PropertyType Properties[];

private:
	Player * m_player;
};

#endif /* end of include guard: LUAPLAYER_H */
