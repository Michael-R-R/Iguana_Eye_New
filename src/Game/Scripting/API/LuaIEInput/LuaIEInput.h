#pragma once

#include <sol/sol.hpp>

class IEInput;

class LuaIEInput
{

public:
    LuaIEInput(IEInput& val, sol::table& gameTable);
    ~LuaIEInput();
};

