#pragma once

#include <sol/sol.hpp>

class IEECS;

class LuaGlobalECS
{
    // DOES NOT OWN THIS POINTER
    IEECS* ecs;

public:
    LuaGlobalECS(IEECS* ecs_, sol::table& gameTable);
    ~LuaGlobalECS();
};

