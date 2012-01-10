#include "lua/LuaClasses.h"
#include "widgets/TextWidget.h"

LuaClass luaTextWidget("TextWidget", &luaWidget);

int LuaTextWidget_new(lua_State *L) {
	std::string name(luaL_checkstring(L, 1));
	lua_pop(L, 1);

	luaTextWidget.push(L, std::make_shared<TextWidget>(name));
	return 1;
}

int LuaTextWidget_color(lua_State *L) {
	TextWidget::Ptr widget = luaTextWidget.check<TextWidget>(L, 1);

	Color color = widget->color();
	lua_pushnumber(L, color.r);
	lua_pushnumber(L, color.g);
	lua_pushnumber(L, color.b);
	lua_pushnumber(L, color.a);
	return 4;
}

int LuaTextWidget_setColor(lua_State *L) {
	TextWidget::Ptr widget = luaTextWidget.check<TextWidget>(L, 1);
	float r = luaL_checknumber(L, 2);
	float g = luaL_checknumber(L, 3);
	float b = luaL_checknumber(L, 4);
	float a = luaL_checknumber(L, 5);
	lua_pop(L, 5);

	widget->setColor(Color(r, g, b, a));
	return 0;
}

int LuaTextWidget_setFont(lua_State *L) {
	TextWidget::Ptr widget = luaTextWidget.check<TextWidget>(L, 1);
	std::string file(luaL_checkstring(L, 2));
	int height = luaL_checkint(L, 3);
	lua_pop(L, 3);

	widget->setFont(file, height);
	return 0;
}


int LuaTextWidget_text(lua_State *L) {
	TextWidget::Ptr widget = luaTextWidget.check<TextWidget>(L, 1);

	lua_pushstring(L, widget->text().c_str());
	return 1;
}

int LuaTextWidget_setText(lua_State *L) {
	TextWidget::Ptr widget = luaTextWidget.check<TextWidget>(L, 1);
	std::string text(luaL_checkstring(L, 2));
	lua_pop(L, 2);

	widget->setText(text);
	return 0;
}

void LuaTextWidget_classSetup(lua_State *L) {
	static const luaL_Reg methods[] = {
		{ "new" , LuaTextWidget_new, },
		{ "color", LuaTextWidget_color },
		{ "setColor", LuaTextWidget_setColor },
		{ "setFont", LuaTextWidget_setFont },
		{ "text", LuaTextWidget_text },
		{ "setText", LuaTextWidget_setText },
		{ 0, 0 },
	};

	static const luaL_Reg meta[] = {
		{ 0, 0 },
	};

	luaTextWidget.registerClass(L, methods, meta);
}
