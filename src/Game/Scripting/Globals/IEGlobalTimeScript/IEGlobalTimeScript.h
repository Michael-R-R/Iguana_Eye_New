#pragma once

#include <sol/sol.hpp>

class IETime;

class IEGlobalTimeScript
{
    // DOES NOT OWN THIS POINTER
    IETime* time;

public:
    IEGlobalTimeScript(IETime* val, sol::table& gameTable);
    ~IEGlobalTimeScript();

    float fps();
    float deltaTime();
};

