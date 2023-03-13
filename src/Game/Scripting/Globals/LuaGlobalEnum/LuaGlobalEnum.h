#pragma once

#include "sol/sol.hpp"

class LuaGlobalEnum
{

public:
    LuaGlobalEnum(sol::table& enumTable);
    ~LuaGlobalEnum();
};

