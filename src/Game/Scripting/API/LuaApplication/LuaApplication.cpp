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
                                           "width", &LuaApplication::viewportWidth,
                                           "height", &LuaApplication::viewportHeight);
}

float LuaApplication::viewportWidth()
{
    return game->viewportSize().x();
}

float LuaApplication::viewportHeight()
{
    return game->viewportSize().y();
}
