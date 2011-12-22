#include <cstring>
#include <string>

#include "Application.h"
#include "Component.h"
#include "GameEngine.h"
#include "Object.h"
#include "lua/LuaClasses.h"

LuaClass luaObject("Object");

int LuaObject_new(lua_State *L) {
	Object *object;
	if (lua_gettop(L) == 1) {
		const char *name = luaL_checkstring(L, 1);
		object = new Object(Application::instance()->engine(), name);
		lua_pop(L, 1);
	} else {
		object = new Object(Application::instance()->engine());
	}
	luaObject.push(L, object);
	return 1;
}

int LuaObject_name(lua_State *L) {
	Object *object = static_cast<Object *>(luaObject.check(L, 1));
	lua_pop(L, 1);

	lua_pushstring(L, object->name().c_str());
	return 1;
}

int LuaObject_setName(lua_State *L) {
	Object *object = static_cast<Object *>(luaObject.check(L, 1));
	const char *name = luaL_checkstring(L, 2);
	lua_pop(L, 2);

	object->setName(name);
	return 0;
}

int LuaObject_type(lua_State *L) {
	Object *object = static_cast<Object *>(luaObject.check(L, 1));
	lua_pop(L, 1);

	switch (object->type()) {
	case ObjectType::Dynamic:    lua_pushstring(L, "dynamic");    break;
	case ObjectType::Static:     lua_pushstring(L, "static");     break;
	case ObjectType::Kinematic:  lua_pushstring(L, "kinematic");  break;
	case ObjectType::Background: lua_pushstring(L, "background"); break;
	default: lua_pushnil(L); break;
	}

	return 1;
}

int LuaObject_setType(lua_State *L) {
	Object *object = static_cast<Object *>(luaObject.check(L, 1));
	const char *typeName = luaL_checkstring(L, 2);
	lua_pop(L, 2);

	ObjectType type = ObjectType::Dynamic;
	if (strcmp(typeName, "static") == 0) {
		type = ObjectType::Static;
	} else if (strcmp(typeName, "kinematic") == 0) {
		type = ObjectType::Dynamic;
	} else if (strcmp(typeName, "background") == 0) {
		type = ObjectType::Background;
	}

	object->setType(type);
	return 0;
}

int LuaObject_component(lua_State *L) {
	Object *object = static_cast<Object *>(luaObject.check(L, 1));
	const char *type = luaL_checkstring(L, 2);
	lua_pop(L, 2);

	LuaClass *luaClass = LuaClass::get(type);
	if (!luaClass)
		luaClass = &luaComponent;

	Component *component = object->component(type);
	if (!component) {
		lua_pushnil(L);
	} else {
		luaClass->push(L, component);
	}
	return 1;
}

int LuaObject_addComponent(lua_State *L) {
	Object *object = static_cast<Object *>(luaObject.check(L, 1));
	Component *component = static_cast<Component *>(luaComponent.check(L, 2));
	lua_pop(L, 2);

	object->addComponent(component);
	return 0;
}

int LuaObject_register(lua_State *L) {
	Object *object = static_cast<Object *>(luaObject.check(L, 1));
	lua_pop(L, 1);

	Application::instance()->engine()->registerObject(object);
	return 0;
}

int LuaObject_unregister(lua_State *L) {
	Object *object = static_cast<Object *>(luaObject.check(L, 1));
	lua_pop(L, 1);

	Application::instance()->engine()->unregisterObject(object);
	return 0;
}

void LuaObject_classSetup(lua_State *L) {
	static const luaL_Reg methods[] = {
		{ "new", LuaObject_new },
		{ "name", LuaObject_name },
		{ "setName", LuaObject_setName },
		{ "type", LuaObject_type},
		{ "setType", LuaObject_setType },
		{ "component", LuaObject_component },
		{ "addComponent", LuaObject_addComponent },
		{ "register", LuaObject_register },
		{ "unregister", LuaObject_unregister },
		{ 0, 0 },
	};

	static const luaL_Reg meta[] = {
		{ 0, 0 },
	};

	luaObject.registerClass(L, methods, meta);
}
