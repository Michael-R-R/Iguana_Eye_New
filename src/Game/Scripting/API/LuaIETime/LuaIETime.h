#pragma once

#include <sol/sol.hpp>

class IETime;

class LuaIETime
{

public:
    LuaIETime(IETime& val, sol::table& gameTable);
    ~LuaIETime();
};

