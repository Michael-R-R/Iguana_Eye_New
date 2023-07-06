#pragma once

#include "sol/sol.hpp"

class LuaUtility
{
    LuaUtility();
    static LuaUtility instance;

public:
    ~LuaUtility();

    static void addToLua(sol::table& utilityTable);

private:
    uint64_t computeHash(const char* str);
};

