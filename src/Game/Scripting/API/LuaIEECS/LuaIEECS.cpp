#include "LuaIEECS.h"
#include "IEECSNameSystem.h"
#include "IEECSScriptSystem.h"
#include "IEECSTransformSystem.h"

LuaIEECS::LuaIEECS(IEECS& ecs_, sol::table& gameTable) :
    ecs(ecs_)
{
    gameTable["ECS"] = this;
    gameTable.new_usertype<LuaIEECS>("", sol::no_constructor,
                                     "nameComponent", &LuaIEECS::nameComponent,
                                     "scriptComponent", &LuaIEECS::scriptComponent,
                                     "transformComponent", &LuaIEECS::transformComponent);
}

IEECSNameSystem* LuaIEECS::nameComponent()
{
    return ecs.getComponent<IEECSNameSystem>("Name");
}

IEECSScriptSystem* LuaIEECS::scriptComponent()
{
    return ecs.getComponent<IEECSScriptSystem>("Script");
}

IEECSTransformSystem* LuaIEECS::transformComponent()
{
    return ecs.getComponent<IEECSTransformSystem>("Transform");
}
