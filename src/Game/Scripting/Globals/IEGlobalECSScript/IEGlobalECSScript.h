#pragma once

#include <sol/sol.hpp>

class IEECS;

class IEGlobalECSScript
{
    // DOES NOT OWN THIS POINTER
    IEECS* ecs;

public:
    IEGlobalECSScript(IEECS* ecs_, sol::table& gameTable);
    ~IEGlobalECSScript();
};

