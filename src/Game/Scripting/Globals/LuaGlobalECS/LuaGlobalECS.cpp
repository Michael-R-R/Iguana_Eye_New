#include "LuaGlobalECS.h"
#include "IEECS.h"

LuaGlobalECS::LuaGlobalECS(IEECS& ecs_, sol::table& gameTable) :
    ecs(ecs_)
{
    gameTable["ECS"] = this;
    gameTable.new_usertype<LuaGlobalECS>("", sol::constructors<>());
}

LuaGlobalECS::~LuaGlobalECS()
{

}
