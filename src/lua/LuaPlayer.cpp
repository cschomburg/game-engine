#include "lua/LuaPlayer.h"

LuaPlayer::LuaPlayer(lua_State * L, bool internal)
  : Player() {}

LuaPlayer::~LuaPlayer() {}

int LuaPlayer::setVelocity(lua_State * L) {
	Player::setVelocity(Vector2(lua_tonumber(L, -2), lua_tonumber(L, -1)));
	return 0;
}

const char * LuaPlayer::className = "Player";
const Luna<LuaPlayer>::FunctionType LuaPlayer::Functions[] = {
	{ "setVelocity", &LuaPlayer::setVelocity },
	{0}
};
const Luna<LuaPlayer>::PropertyType LuaPlayer::Properties[] = {
	{0}
};
