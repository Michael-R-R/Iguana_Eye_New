#include "LuaIEEntity.h"
#include "IEEntity.h"

LuaIEEntity::LuaIEEntity(sol::state& lua)
{
    lua.new_usertype<IEEntity>("IEEntity", sol::constructors<IEEntity(const int)>(),
                               "id", sol::property(&IEEntity::getId));
}
