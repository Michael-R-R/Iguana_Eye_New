#include "LuaApplication.h"
#include "IEGame.h"

LuaApplication::LuaApplication(IEGame& game_, sol::table gameTable) :
    game(game_)
{
    gameTable["Application"] = this;
    gameTable.new_usertype<LuaApplication>("", sol::no_constructor,
                                           "viewportWidth", &LuaApplication::viewportWidth,
                                           "viewportHeight", &LuaApplication::viewportHeight);
}

LuaApplication::~LuaApplication()
{

}

float LuaApplication::viewportWidth()
{
    return (float)game.viewportSize().first;
}

float LuaApplication::viewportHeight()
{
    return (float)game.viewportSize().second;
}
