#pragma once

#include <sol/sol.hpp>

class IEECS;

class LuaGlobalECS
{
    IEECS& ecs;

public:
    LuaGlobalECS(IEECS& ecs_, sol::table& gameTable);
    ~LuaGlobalECS();
};

