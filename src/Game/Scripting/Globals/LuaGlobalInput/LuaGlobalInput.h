#pragma once

#include <sol/sol.hpp>

class IEInput;

class LuaGlobalInput
{
    IEInput& input;

public:
    LuaGlobalInput(IEInput& val, sol::table& gameTable);
    ~LuaGlobalInput();

    bool isPressed(const char* keyName);
};

