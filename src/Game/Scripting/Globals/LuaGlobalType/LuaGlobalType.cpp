#include "LuaGlobalType.h"
#include "IEEntity.h"
#include "IEScript.h"
#include "IEECSScriptSystem.h"

LuaGlobalType::LuaGlobalType(sol::state& lua)
{
    setupIEEntity(lua);
    setupIEScript(lua);
    setupIEComponents(lua);
}

void LuaGlobalType::setupIEEntity(sol::state& lua)
{
    lua.new_usertype<IEEntity>("IEEntity", sol::constructors<IEEntity(), IEEntity(const int)>(),
                              "id", sol::property(&IEEntity::getId));
}

void LuaGlobalType::setupIEScript(sol::state& lua)
{
    lua.new_usertype<IEScript>("", sol::no_constructor,
                               "value", &IEScript::value,
                               "getFunc", &IEScript::getFunc,
                               "callFunc", &IEScript::callFunc);
}

void LuaGlobalType::setupIEComponents(sol::state& lua)
{
    lua.new_usertype<IEECSScriptSystem>("", sol::no_constructor,
                                        "lookUpIndex", &IEECSScriptSystem::lookUpIndex,
                                        "getScript", sol::overload(sol::resolve<const int, const unsigned long long>(&IEECSScriptSystem::getScript),
                                                                   sol::resolve<const int, const char*>(&IEECSScriptSystem::getScript)));
}
