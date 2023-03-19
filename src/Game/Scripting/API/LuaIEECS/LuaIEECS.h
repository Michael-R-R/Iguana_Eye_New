#pragma once

#include <sol/sol.hpp>

#include "IEECS.h"

class IEECSNameSystem;
class IEECSInputSystem;
class IEECSScriptSystem;
class IEECSTransformSystem;
class IEECSCameraSystem;

class LuaIEECS
{
    LuaIEECS();
    static LuaIEECS instance;

    // DOES NOT OWN THIS POINTER
    IEECS* ecs;

public:
    ~LuaIEECS();

    static void addToLua(IEECS* val, sol::state& lua, sol::table& gameTable);

private:
    IEECSNameSystem* nameComponent();
    IEECSInputSystem* inputComponent();
    IEECSScriptSystem* scriptComponent();
    IEECSTransformSystem* transformComponent();
    IEECSCameraSystem* cameraComponent();
};

