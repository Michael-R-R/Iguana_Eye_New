#pragma once

#include <sol/sol.hpp>

class IETime;

class LuaGlobalTime
{
    IETime& time;

public:
    LuaGlobalTime(IETime& val, sol::table& gameTable);
    ~LuaGlobalTime();

    float fps();
    float deltaTime();
};

