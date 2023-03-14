#pragma once

#include <sol/sol.hpp>
#include <memory>

#include "IEObject.h"

class GameStartEvent;
class LuaUtility;
class LuaEnum;
class LuaIEEntity;
class LuaIEScript;
class LuaIETime;
class LuaIEInput;
class LuaIEECS;
class LuaIEECSScriptSystem;

class IEScriptEngine : public IEObject
{
    sol::state lua;

    std::unique_ptr<LuaEnum> luaEnum;
    std::unique_ptr<LuaUtility> luaUtility;
    std::unique_ptr<LuaIEEntity> luaEntity;
    std::unique_ptr<LuaIEScript> luaScript;
    std::unique_ptr<LuaIETime> luaTime;
    std::unique_ptr<LuaIEInput> luaInput;
    std::unique_ptr<LuaIEECS> luaECS;
    std::unique_ptr<LuaIEECSScriptSystem> luaScriptSystem;

public:
    IEScriptEngine();
    ~IEScriptEngine();

    void startup(const GameStartEvent& event);
    void shutdown();

    sol::state& getLua() { return lua; }
};

