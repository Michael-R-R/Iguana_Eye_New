#include "IEGlobalECSScript.h"
#include "IEECS.h"

IEGlobalECSScript::IEGlobalECSScript(IEECS* ecs_, sol::table& gameTable) :
    ecs(ecs_)
{
    gameTable["ECS"] = this;
    gameTable.new_usertype<IEGlobalECSScript>("", sol::constructors<>());
}

IEGlobalECSScript::~IEGlobalECSScript()
{

}
