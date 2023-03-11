#include "LuaGlobalTime.h"
#include "IETime.h"

LuaGlobalTime::LuaGlobalTime(IETime* val, sol::table& gameTable) :
    time(val)
{
    gameTable["IETime"] = this;
    gameTable.new_usertype<LuaGlobalTime>("", sol::constructors<>(),
                                               "fps", &LuaGlobalTime::fps,
                                               "deltaTime", &LuaGlobalTime::deltaTime);
}

LuaGlobalTime::~LuaGlobalTime()
{
    time = nullptr;
}

float LuaGlobalTime::fps()
{
    return time->getFPS();
}

float LuaGlobalTime::deltaTime()
{
    return time->getDeltaTime();
}
