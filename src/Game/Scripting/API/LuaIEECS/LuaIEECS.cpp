#include "LuaIEECS.h"
#include "IEECSNameSystem.h"
#include "IEECSInputSystem.h"
#include "IEECSScriptSystem.h"
#include "IEECSTransformSystem.h"
#include "IEECSCameraSystem.h"

LuaIEECS::LuaIEECS(IEECS& ecs_, sol::state& lua,  sol::table& gameTable) :
    ecs(ecs_),
    luaEntity(std::make_unique<LuaIEEntity>(lua))
{
    gameTable["ECS"] = this;
    gameTable.new_usertype<LuaIEECS>("", sol::no_constructor,
                                     "nameComponent", &LuaIEECS::nameComponent,
                                     "inputComponent", &LuaIEECS::inputComponent,
                                     "scriptComponent", &LuaIEECS::scriptComponent,
                                     "transformComponent", &LuaIEECS::transformComponent,
                                     "cameraComponent", &LuaIEECS::cameraComponent);
}

LuaIEECS::~LuaIEECS()
{

}

IEECSNameSystem* LuaIEECS::nameComponent()
{
    return ecs.getComponent<IEECSNameSystem>("Name");
}

IEECSInputSystem* LuaIEECS::inputComponent()
{
    return ecs.getComponent<IEECSInputSystem>("Input");
}

IEECSScriptSystem* LuaIEECS::scriptComponent()
{
    return ecs.getComponent<IEECSScriptSystem>("Script");
}

IEECSTransformSystem* LuaIEECS::transformComponent()
{
    return ecs.getComponent<IEECSTransformSystem>("Transform");
}

IEECSCameraSystem* LuaIEECS::cameraComponent()
{
    return ecs.getComponent<IEECSCameraSystem>("Camera");
}
