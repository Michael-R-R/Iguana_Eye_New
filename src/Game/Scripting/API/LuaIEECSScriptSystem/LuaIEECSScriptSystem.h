#pragma once

#include <sol/sol.hpp>
#include <memory>

#include "LuaIEScript.h"

class LuaIEECSScriptSystem
{
    std::unique_ptr<LuaIEScript> luaScript;

public:
    LuaIEECSScriptSystem(sol::state& lua);
    ~LuaIEECSScriptSystem();
};

