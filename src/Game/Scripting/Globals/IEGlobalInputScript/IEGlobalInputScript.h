#pragma once

#include <sol/sol.hpp>

class IEInput;

class IEGlobalInputScript
{
    // DOES NOT OWN THIS POINTER
    IEInput* input;

public:
    IEGlobalInputScript(IEInput* val, sol::table& gameTable);
    ~IEGlobalInputScript();

    bool isPressed(const char* keyName);
};

