#include "LuaIEECSInputSystem.h"
#include "IEECSInputSystem.h"

void LuaIEECSInputSystem::addToLua(sol::state& lua)
{
    lua.new_usertype<IEECSInputSystem>("", sol::no_constructor,
                                       "lookUpIndex", &IEECSInputSystem::lookUpIndex,
                                       "getHasInput", &IEECSInputSystem::getHasInput,
                                       "setHasInput", &IEECSInputSystem::setHasInput);
}
