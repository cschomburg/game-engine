#include "lua/LuaEntity.h"

LuaEntity::LuaEntity() {}

LuaEntity::LuaEntity(lua_State * L, bool internal) {
	m_entity = new Entity();
}

LuaEntity::LuaEntity(Entity * entity) {
	m_entity = entity;
}

LuaEntity::~LuaEntity() {
	if (!isExisting && m_entity) {
		delete m_entity;
		m_entity = 0;
	}
}

int LuaEntity::velocity(lua_State * L) {
	if (!m_entity)
		return luaL_error(L, "Lua object is non-existing");

	lua_pushnumber(L, m_entity->velocity().x);
	lua_pushnumber(L, m_entity->velocity().y);
	return 2;
}

int LuaEntity::setVelocity(lua_State * L) {
	if (!m_entity)
		return luaL_error(L, "Lua object is non-existing");

	m_entity->setVelocity(Vector2(lua_tonumber(L, -2),
				                  lua_tonumber(L, -1)));
	return 0;
}

int LuaEntity::acceleration(lua_State * L) {
	if (!m_entity)
		return luaL_error(L, "Lua object is non-existing");

	lua_pushnumber(L, m_entity->acceleration().x);
	lua_pushnumber(L, m_entity->acceleration().y);
	return 2;
}

int LuaEntity::setAcceleration(lua_State * L) {
	if (!m_entity)
		return luaL_error(L, "Lua object is non-existing");

	m_entity->setAcceleration(Vector2(lua_tonumber(L, -2),
				                  lua_tonumber(L, -1)));
	return 0;
}
const char * LuaEntity::className = "Entity";
const Luna<LuaEntity>::FunctionType LuaEntity::Functions[] = {
	{ "velocity", &LuaEntity::velocity },
	{ "setVelocity", &LuaEntity::setVelocity },
	{ "acceleration", &LuaEntity::acceleration},
	{ "setAcceleration", &LuaEntity::setAcceleration },
	{0}
};
const Luna<LuaEntity>::PropertyType LuaEntity::Properties[] = {
	{0}
};
