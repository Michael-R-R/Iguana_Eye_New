#include "LuaIEECS.h"
#include "LuaIEEntity.h"
#include "LuaIEECSInputSystem.h"
#include "LuaIEECSScriptSystem.h"
#include "LuaIEECSTransformSystem.h"
#include "LuaIEECSCameraSystem.h"
#include "IEECSNameSystem.h"
#include "IEECSInputSystem.h"
#include "IEECSScriptSystem.h"
#include "IEECSTransformSystem.h"
#include "IEECSCameraSystem.h"

LuaIEECS LuaIEECS::instance;

LuaIEECS::LuaIEECS() :
    ecs(nullptr)
{

}

LuaIEECS::~LuaIEECS()
{
    ecs = nullptr;
}

void LuaIEECS::addToLua(IEECS* val, sol::state& lua, sol::table& gameTable)
{
    LuaIEEntity::addToLua(lua);
    LuaIEECSInputSystem::addToLua(lua);
    LuaIEECSScriptSystem::addToLua(lua);
    LuaIEECSTransformSystem::addToLua(lua);
    LuaIEECSCameraSystem::addToLua(lua);

    instance.ecs = val;

    gameTable["ECS"] = instance;
    gameTable.new_usertype<LuaIEECS>("", sol::no_constructor,
                                     "nameComponent", &LuaIEECS::nameComponent,
                                     "inputComponent", &LuaIEECS::inputComponent,
                                     "scriptComponent", &LuaIEECS::scriptComponent,
                                     "transformComponent", &LuaIEECS::transformComponent,
                                     "cameraComponent", &LuaIEECS::cameraComponent);
}

IEECSNameSystem* LuaIEECS::nameComponent()
{
    return ecs->getComponent<IEECSNameSystem>("Name");
}

IEECSInputSystem* LuaIEECS::inputComponent()
{
    return ecs->getComponent<IEECSInputSystem>("Input");
}

IEECSScriptSystem* LuaIEECS::scriptComponent()
{
    return ecs->getComponent<IEECSScriptSystem>("Script");
}

IEECSTransformSystem* LuaIEECS::transformComponent()
{
    return ecs->getComponent<IEECSTransformSystem>("Transform");
}

IEECSCameraSystem* LuaIEECS::cameraComponent()
{
    return ecs->getComponent<IEECSCameraSystem>("Camera");
}
