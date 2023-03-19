#include "LuaIEScript.h"
#include "IEScript.h"

void LuaIEScript::addToLua(sol::state& lua)
{
    lua.new_usertype<IEScript>("", sol::no_constructor,
                               "id", sol::property(&IEScript::getId),
                               "value", &IEScript::value,
                               "getFunc", &IEScript::getFunc,
                               "callFunc", &IEScript::callFunc);
}
