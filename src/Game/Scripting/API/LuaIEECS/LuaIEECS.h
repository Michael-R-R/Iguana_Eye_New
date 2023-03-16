#pragma once

#include <sol/sol.hpp>

#include "IEECS.h"

class IEECSNameSystem;
class IEECSScriptSystem;
class IEECSTransformSystem;

class LuaIEECS
{
    IEECS& ecs;

public:
    LuaIEECS(IEECS& ecs_, sol::table& gameTable);
    ~LuaIEECS() {}

private:
    IEECSNameSystem* nameComponent();
    IEECSScriptSystem* scriptComponent();
    IEECSTransformSystem* transformComponent();
};

