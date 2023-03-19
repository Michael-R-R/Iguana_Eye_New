#pragma once

#include "sol/sol.hpp"

class LuaEnum
{

public:
    static void addToLua(sol::table& enumTable);
};

