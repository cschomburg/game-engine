#ifndef LUAENTITY_H
#define LUAENTITY_H

#include "lua/LuaObject.h"
#include "Entity.h"

class LuaEntity : public LuaObject {
public:
	LuaEntity();
	LuaEntity(lua_State * L, bool internal);
	LuaEntity(Entity * entity);
	virtual ~LuaEntity();

	int velocity(lua_State * L);
	int setVelocity(lua_State * L);

public:
	static const char * className;
	static const Luna<LuaEntity>::FunctionType Functions[];
	static const Luna<LuaEntity>::PropertyType Properties[];

private:
	Entity * m_entity;
};

#endif /* end of include guard: LUAENTITY_H */
