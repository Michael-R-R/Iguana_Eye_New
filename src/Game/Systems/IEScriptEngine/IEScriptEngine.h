#pragma once

#include <sol/sol.hpp>
#include <memory>

#include "IEObject.h"

class GameStartEvent;
class LuaGlobalType;
class LuaGlobalEnum;
class LuaGlobalTime;
class LuaGlobalInput;
class LuaGlobalECS;

class IEScriptEngine : public IEObject
{
    sol::state lua;

    std::unique_ptr<LuaGlobalType> globalType;
    std::unique_ptr<LuaGlobalEnum> globalEnum;
    std::unique_ptr<LuaGlobalTime> globalTime;
    std::unique_ptr<LuaGlobalInput> globalInput;
    std::unique_ptr<LuaGlobalECS> globalECS;

public:
    IEScriptEngine();
    ~IEScriptEngine();

    void startup(const GameStartEvent& event);
    void shutdown();

    sol::state& getLua() { return lua; }
};

