#pragma once

#include <sol/sol.hpp>

class IETime;

class LuaIETime
{
    LuaIETime();
    static LuaIETime instance;

    // DOES NOT OWN THIS POINTER
    IETime* time;

public:
    ~LuaIETime();

    static void addToLua(IETime* val, sol::table& gameTable);

private:
    float fps();
    float deltaTime();
};

