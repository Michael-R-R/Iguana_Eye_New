#pragma once

#include <sol/sol.hpp>

class IEGame;

class LuaApplication
{
    IEGame& game;

public:
    LuaApplication(IEGame& game_, sol::table gameTable);
    ~LuaApplication();

    float viewportWidth();
    float viewportHeight();
};

