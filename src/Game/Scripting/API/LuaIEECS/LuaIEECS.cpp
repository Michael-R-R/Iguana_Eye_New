#include "LuaIEECS.h"
#include "IEECSNameSystem.h"
#include "IEECSScriptSystem.h"

LuaIEECS::LuaIEECS(IEECS& ecs_, sol::table& gameTable) :
    ecs(ecs_)
{
    gameTable["ECS"] = this;
    gameTable.new_usertype<LuaIEECS>("", sol::no_constructor,
                                     "getNameComponent", &LuaIEECS::getNameComponent,
                                     "getScriptComponent", &LuaIEECS::getScriptComponent);
}

IEECSNameSystem* LuaIEECS::getNameComponent()
{
    return ecs.getComponent<IEECSNameSystem>("Name");
}

IEECSScriptSystem* LuaIEECS::getScriptComponent()
{
    return ecs.getComponent<IEECSScriptSystem>("Script");
}
