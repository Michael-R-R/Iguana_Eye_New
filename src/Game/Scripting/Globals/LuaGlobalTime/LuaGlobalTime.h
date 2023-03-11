#pragma once

#include <sol/sol.hpp>

class IETime;

class LuaGlobalTime
{
    // DOES NOT OWN THIS POINTER
    IETime* time;

public:
    LuaGlobalTime(IETime* val, sol::table& gameTable);
    ~LuaGlobalTime();

    float fps();
    float deltaTime();
};

