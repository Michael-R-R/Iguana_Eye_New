#include "LuaApplication.h"
#include "IEGame.h"

LuaApplication LuaApplication::instance;

LuaApplication::LuaApplication() :
    game(nullptr)
{

}

LuaApplication::~LuaApplication()
{
    game = nullptr;
}

void LuaApplication::addToLua(IEGame* val, sol::table gameTable)
{
    instance.game = val;

    gameTable["Application"] = instance;
    gameTable.new_usertype<LuaApplication>("", sol::no_constructor,
                                           "viewportWidth", &LuaApplication::viewportWidth,
                                           "viewportHeight", &LuaApplication::viewportHeight);
}

float LuaApplication::viewportWidth()
{
    return (float)game->viewportSize().first;
}

float LuaApplication::viewportHeight()
{
    return (float)game->viewportSize().second;
}
