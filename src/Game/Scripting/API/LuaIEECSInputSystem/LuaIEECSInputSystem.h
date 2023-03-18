#pragma once

#include <sol/sol.hpp>

#include "IEEntity.h"

class LuaIEECSInputSystem
{
public:
    LuaIEECSInputSystem(sol::state& lua);
    ~LuaIEECSInputSystem();

};

