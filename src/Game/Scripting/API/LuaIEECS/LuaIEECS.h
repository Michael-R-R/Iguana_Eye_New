#pragma once

#include <sol/sol.hpp>

#include "IEECS.h"

class IEECSNameSystem;
class IEECSScriptSystem;

class LuaIEECS
{
    IEECS& ecs;

public:
    LuaIEECS(IEECS& ecs_, sol::table& gameTable);
    ~LuaIEECS() {}

private:
    IEECSNameSystem* getNameComponent();
    IEECSScriptSystem* getScriptComponent();
};

