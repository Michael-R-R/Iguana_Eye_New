#pragma once

#include <sol/sol.hpp>

#include "IEECS.h"
#include "LuaIEEntity.h"

class LuaIEEntity;
class IEECSNameSystem;
class IEECSInputSystem;
class IEECSScriptSystem;
class IEECSTransformSystem;
class IEECSCameraSystem;

class LuaIEECS
{
    IEECS& ecs;
    std::unique_ptr<LuaIEEntity> luaEntity;

public:
    LuaIEECS(IEECS& ecs_, sol::state& lua, sol::table& gameTable);
    ~LuaIEECS();

private:
    IEECSNameSystem* nameComponent();
    IEECSInputSystem* inputComponent();
    IEECSScriptSystem* scriptComponent();
    IEECSTransformSystem* transformComponent();
    IEECSCameraSystem* cameraComponent();
};

