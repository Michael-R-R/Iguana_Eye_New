#pragma once

#include <sol/sol.hpp>

class LuaIEECSTransformSystem
{

public:
    LuaIEECSTransformSystem(sol::state& lua);
    ~LuaIEECSTransformSystem() {}
};

