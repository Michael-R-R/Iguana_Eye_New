#pragma once

#include <sol/sol.hpp>
#include <memory>

class LuaIECamera;

class LuaIEECSCameraSystem
{
    std::unique_ptr<LuaIECamera> luaCamera;

public:
    LuaIEECSCameraSystem(sol::state& lua);
    ~LuaIEECSCameraSystem();
};

