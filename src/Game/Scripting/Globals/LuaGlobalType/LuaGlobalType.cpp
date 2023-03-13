#include "LuaGlobalType.h"
#include "IEScript.h"
#include "IEEntity.h"

LuaGlobalType::LuaGlobalType(sol::state& lua)
{
    setupIEEntity(lua);
    setupIEScript(lua);
}

void LuaGlobalType::setupIEEntity(sol::state& lua)
{
    lua.new_usertype<IEEntity>("", sol::no_constructor,
                              "id", sol::property(&IEEntity::getId));
}

void LuaGlobalType::setupIEScript(sol::state& lua)
{
    lua.new_usertype<IEScript>("", sol::no_constructor,
                               "value", &IEScript::value,
                               "func", &IEScript::func);
}

void LuaGlobalType::setupIEComponents(sol::state& lua)
{

}
