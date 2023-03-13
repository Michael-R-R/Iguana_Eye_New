#include "LuaGlobalECS.h"
#include "IEECSNameSystem.h"
#include "IEECSScriptSystem.h"

LuaGlobalECS::LuaGlobalECS(IEECS& ecs_, sol::table& gameTable) :
    ecs(ecs_)
{
    gameTable["ECS"] = this;
    gameTable.new_usertype<LuaGlobalECS>("", sol::no_constructor,
                                         "getNameComponent", &LuaGlobalECS::getNameComponent,
                                         "getScriptComponent", &LuaGlobalECS::getScriptComponent);
}

IEECSNameSystem* LuaGlobalECS::getNameComponent()
{
    return ecs.getComponent<IEECSNameSystem>(IEComponentType::Name);
}

IEECSScriptSystem* LuaGlobalECS::getScriptComponent()
{
    return ecs.getComponent<IEECSScriptSystem>(IEComponentType::Script);
}
