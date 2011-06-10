#include "lua/LuaPlayer.h"

LuaPlayer::LuaPlayer(lua_State * L, bool internal) {
	  m_player = new Player();
	  LuaEntity(m_player);
}

LuaPlayer::LuaPlayer(Player * player)
  : LuaEntity(player) {
	  m_player = player;
}

LuaPlayer::~LuaPlayer() {}

const char * LuaPlayer::className = "Player";
const Luna<LuaPlayer>::FunctionType LuaPlayer::Functions[] = {
	{ "velocity", &LuaEntity::velocity },
	{ "setVelocity", &LuaEntity::setVelocity },
	{ "acceleration", &LuaEntity::acceleration },
	{ "setAcceleration", &LuaEntity::setAcceleration },
	{0}
};
const Luna<LuaPlayer>::PropertyType LuaPlayer::Properties[] = {
	{0}
};
