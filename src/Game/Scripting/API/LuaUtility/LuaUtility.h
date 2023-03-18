#pragma once

#include "sol/sol.hpp"

class LuaUtility
{

public:
    LuaUtility(sol::table& utilityTable);
    ~LuaUtility();

private:
    unsigned long long computeHash(const char* str);
};

