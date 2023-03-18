#pragma once

#include <sol/sol.hpp>

class LuaIECamera
{

public:
    LuaIECamera(sol::state& lua);
    ~LuaIECamera();
};

