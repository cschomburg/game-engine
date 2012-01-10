#include "GameEngine.h"
#include "lua/LuaClasses.h"
#include "Widget.h"

LuaClass luaWidget("Widget");

int LuaWidget_new(lua_State *L) {
	std::string name(luaL_checkstring(L, 1));
	Widget::Ptr parent;
	if (lua_gettop(L) >= 2) {
		parent = luaWidget.check<Widget>(L, 2);
	}
	lua_pop(L, lua_gettop(L));

	luaWidget.push(L, std::make_shared<Widget>("Widget", name));
	return 1;
}

int LuaWidget_type(lua_State *L) {
	Widget::Ptr widget = luaWidget.check<Widget>(L, 1);
	lua_pop(L, 1);

	lua_pushstring(L, widget->type().c_str());
	return 1;
}

int LuaWidget_parent(lua_State *L) {
	Widget::Ptr widget = luaWidget.check<Widget>(L, 1);
	lua_pop(L, 1);

	Widget::Ptr parent = widget->parent();
	if (!parent) {
		return 0;
	}

	LuaClass::get(parent->type())->push(L, parent);
	return 1;
}

int LuaWidget_setParent(lua_State *L) {
	Widget::Ptr widget = luaWidget.check<Widget>(L, 1);
	Widget::Ptr parent;
	if (lua_gettop(L) >= 2 && !lua_isnil(L, 2)) {
		parent = luaWidget.check<Widget>(L, 2);
	}
	lua_pop(L, lua_gettop(L));

	widget->setParent(parent);
	return 0;
}

int LuaWidget_isShown(lua_State *L) {
	Widget::Ptr widget = luaWidget.check<Widget>(L, 1);
	lua_pushboolean(L, widget->isShown());
	return 1;
}

int LuaWidget_setShown(lua_State *L) {
	Widget::Ptr widget = luaWidget.check<Widget>(L, 1);
	bool shown = lua_gettop(L) >= 2 && !lua_isnil(L, 2);
	lua_pop(L, lua_gettop(L));

	widget->setShown(shown);
	return 0;
}

int LuaWidget_rect(lua_State *L) {
	Widget::Ptr widget = luaWidget.check<Widget>(L, 1);
	lua_pushnumber(L, widget->rect().bottomLeft().x);
	lua_pushnumber(L, widget->rect().bottomLeft().y);
	lua_pushnumber(L, widget->rect().size().x);
	lua_pushnumber(L, widget->rect().size().y);
	return 4;
}

int LuaWidget_setRect(lua_State *L) {
	Widget::Ptr widget = luaWidget.check<Widget>(L, 1);
	float x = luaL_checknumber(L, 2);
	float y = luaL_checknumber(L, 3);
	float w = luaL_checknumber(L, 4);
	float h = luaL_checknumber(L, 5);
	lua_pop(L, 5);

	widget->setRect(Rect(x, y, w, h));
	return 0;
}

int LuaWidget_pos(lua_State *L) {
	Widget::Ptr widget = luaWidget.check<Widget>(L, 1);
	lua_pushnumber(L, widget->rect().bottomLeft().x);
	lua_pushnumber(L, widget->rect().bottomLeft().y);
	return 2;
}

int LuaWidget_setPos(lua_State *L) {
	Widget::Ptr widget = luaWidget.check<Widget>(L, 1);
	float x = luaL_checknumber(L, 2);
	float y = luaL_checknumber(L, 3);
	lua_pop(L, 3);

	widget->setPos(Vector2(x, y));
	return 0;
}

int LuaWidget_size(lua_State *L) {
	Widget::Ptr widget = luaWidget.check<Widget>(L, 1);
	lua_pushnumber(L, widget->rect().size().x);
	lua_pushnumber(L, widget->rect().size().y);
	return 2;
}

int LuaWidget_setSize(lua_State *L) {
	Widget::Ptr widget = luaWidget.check<Widget>(L, 1);
	float w = luaL_checknumber(L, 2);
	float h = luaL_checknumber(L, 3);
	lua_pop(L, 3);

	widget->setSize(Vector2(w, h));
	return 0;
}

void LuaWidget_classSetup(lua_State *L) {
	static const luaL_Reg methods[] = {
		{ "new" , LuaWidget_new, },
		{ "type", LuaWidget_type },
		{ "parent", LuaWidget_parent },
		{ "setParent", LuaWidget_setParent },
		{ "isShown", LuaWidget_isShown },
		{ "rect", LuaWidget_rect },
		{ "setRect", LuaWidget_setRect },
		{ "pos", LuaWidget_pos },
		{ "setPos", LuaWidget_setPos },
		{ "size", LuaWidget_setSize },
		{ "setSize", LuaWidget_setSize },
		{ 0, 0 },
	};

	static const luaL_Reg meta[] = {
		{ 0, 0 },
	};

	luaWidget.registerClass(L, methods, meta);
}
