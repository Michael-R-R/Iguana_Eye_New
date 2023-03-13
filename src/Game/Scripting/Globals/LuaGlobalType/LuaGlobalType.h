#pragma once

#include <sol/sol.hpp>

class LuaGlobalType
{

public:
    LuaGlobalType(sol::state& lua);
    ~LuaGlobalType() {}

private:
    void setupIEEntity(sol::state& lua);
    void setupIEScript(sol::state& lua);
    void setupIEComponents(sol::state& lua);
};

