#pragma once

#include <sol/sol.hpp>

class IEGame;

class LuaApplication
{
    LuaApplication();
    static LuaApplication instance;

    // DOES NOT OWN THIS POINTER
    IEGame* game;

public:
    ~LuaApplication();

    static void addToLua(IEGame* val, sol::table gameTable);

private:
    float viewportWidth();
    float viewportHeight();
};

