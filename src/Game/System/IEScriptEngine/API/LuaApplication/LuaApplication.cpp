#include "LuaApplication.h"
#include "ApplicationProperties.h"

LuaApplication LuaApplication::instance;

LuaApplication::LuaApplication()
{

}

LuaApplication::~LuaApplication()
{

}

void LuaApplication::addToLua(sol::table gameTable)
{
    gameTable["IEApplication"] = instance;
    gameTable.new_usertype<LuaApplication>("", sol::no_constructor,
                                           "width", &LuaApplication::viewportWidth,
                                           "height", &LuaApplication::viewportHeight);
}

float LuaApplication::viewportWidth()
{
    return ApplicationProperties::viewportDimensions[0];
}

float LuaApplication::viewportHeight()
{
    return ApplicationProperties::viewportDimensions[1];
}
