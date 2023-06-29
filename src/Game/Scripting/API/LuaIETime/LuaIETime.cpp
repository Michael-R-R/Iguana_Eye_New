#include "LuaIETime.h"
#include "IETime.h"

LuaIETime LuaIETime::instance;

LuaIETime::LuaIETime() :
    time(nullptr)
{

}

LuaIETime::~LuaIETime()
{
    time = nullptr;
}

void LuaIETime::addToLua(IETime* val, sol::table& gameTable)
{
    instance.time = val;

    gameTable["IETime"] = instance;
    gameTable.new_usertype<LuaIETime>("", sol::no_constructor,
                                      "fps", &LuaIETime::fps,
                                      "dt", &LuaIETime::deltaTime);
}

float LuaIETime::fps()
{
    return time->getFPS();
}

float LuaIETime::deltaTime()
{
    return time->getDeltaTime();
}
