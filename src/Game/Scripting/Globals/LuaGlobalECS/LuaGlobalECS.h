#pragma once

#include <sol/sol.hpp>

#include "IEECS.h"

class IEECSSystem;
class IEECSNameSystem;
class IEECSScriptSystem;

class LuaGlobalECS
{
    IEECS& ecs;

public:
    LuaGlobalECS(IEECS& ecs_, sol::table& gameTable);
    ~LuaGlobalECS() {}

private:
    IEECSNameSystem* getNameComponent();
    IEECSScriptSystem* getScriptComponent();
};

