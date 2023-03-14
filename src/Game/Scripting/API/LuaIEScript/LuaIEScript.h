#pragma once

#include <sol/sol.hpp>

class LuaIEScript
{

public:
    LuaIEScript(sol::state& lua);
    ~LuaIEScript() {}
};

