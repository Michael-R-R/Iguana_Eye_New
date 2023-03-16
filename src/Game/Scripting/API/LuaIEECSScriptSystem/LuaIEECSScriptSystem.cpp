#include "LuaIEECSScriptSystem.h"
#include "IEECSScriptSystem.h"

LuaIEECSScriptSystem::LuaIEECSScriptSystem(sol::state& lua)
{
    lua.new_usertype<IEECSScriptSystem>("", sol::no_constructor,
                                        "lookUpIndex", &IEECSScriptSystem::lookUpIndex,
                                        "hasScript", &IEECSScriptSystem::hasScript,
                                        "initScript", &IEECSScriptSystem::initalizeScript,
                                        "startScript", &IEECSScriptSystem::startScript,
                                        "wakeScript", &IEECSScriptSystem::wakeScript,
                                        "sleepScript", &IEECSScriptSystem::sleepScript,
                                        "getScript", sol::overload(sol::resolve<const int, const unsigned long long>(&IEECSScriptSystem::getScript),
                                                                   sol::resolve<const int, const char*>(&IEECSScriptSystem::getScript)));
}
