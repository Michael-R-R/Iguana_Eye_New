#pragma once

#include <sol/sol.hpp>

class IEGame;

class LuaApplication
{
    LuaApplication();
    static LuaApplication instance;

public:
    ~LuaApplication();

    static void addToLua(sol::table gameTable);

private:
    float viewportWidth();
    float viewportHeight();
};

