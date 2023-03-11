#pragma once

#include <sol/sol.hpp>

#include "IEObject.h"

class GameStartEvent;
class LuaGlobalTime;
class LuaGlobalInput;
class LuaGlobalECS;

class IEScriptEngine : public IEObject
{
    sol::state lua;

    std::unique_ptr<LuaGlobalTime> globalTime;
    std::unique_ptr<LuaGlobalInput> globalInput;
    std::unique_ptr<LuaGlobalECS> globalECS;

public:
    IEScriptEngine();
    ~IEScriptEngine();

    void startup(const GameStartEvent& event);
    void shutdown();

    sol::state& getLua() { return lua; }

private:
    void addGlobalUserTypes();
};

