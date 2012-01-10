#include <stdexcept>

#include "lua/LuaClasses.h"
#include "widgets/SolidWidget.h"

LuaClass luaSolidWidget("SolidWidget", &luaWidget);

int LuaSolidWidget_new(lua_State *L) {
	std::string name(luaL_checkstring(L, 1));
	lua_pop(L, 1);

	SolidWidget::Ptr widget = std::make_shared<SolidWidget>(name);
	luaSolidWidget.push(L, widget);
	return 1;
}

int LuaSolidWidget_color(lua_State *L) {
	SolidWidget::Ptr widget = luaSolidWidget.check<SolidWidget>(L, 1);

	Color color = widget->color();
	lua_pushnumber(L, color.r);
	lua_pushnumber(L, color.g);
	lua_pushnumber(L, color.b);
	lua_pushnumber(L, color.a);
	return 4;
}

int LuaSolidWidget_setColor(lua_State *L) {
	SolidWidget::Ptr widget = luaSolidWidget.check<SolidWidget>(L, 1);
	float r = luaL_checknumber(L, 2);
	float g = luaL_checknumber(L, 3);
	float b = luaL_checknumber(L, 4);
	float a = luaL_checknumber(L, 5);
	lua_pop(L, 5);

	widget->setColor(Color(r, g, b, a));
	return 0;
}


void LuaSolidWidget_classSetup(lua_State *L) {
	static const luaL_Reg methods[] = {
		{ "new" , LuaSolidWidget_new, },
		{ "color", LuaSolidWidget_color },
		{ "setColor", LuaSolidWidget_setColor },
		{ 0, 0 },
	};

	static const luaL_Reg meta[] = {
		{ 0, 0 },
	};

	luaSolidWidget.registerClass(L, methods, meta);
}
