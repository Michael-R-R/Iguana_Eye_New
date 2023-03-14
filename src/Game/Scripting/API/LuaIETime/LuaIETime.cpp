#include "LuaIETime.h"
#include "IETime.h"

LuaIETime::LuaIETime(IETime& val, sol::table& gameTable)
{
    gameTable["IETime"] = &val;
    gameTable.new_usertype<IETime>("", sol::no_constructor,
                                   "fps", &IETime::getFPS,
                                   "deltaTime", &IETime::getDeltaTime);
}

LuaIETime::~LuaIETime()
{

}
