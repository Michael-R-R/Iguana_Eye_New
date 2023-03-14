#pragma once

#include "sol/sol.hpp"

class LuaEnum
{

public:
    LuaEnum(sol::table& enumTable);
    ~LuaEnum();
};

