#pragma once

#include <sol/sol.hpp>

#include "IEObject.h"
#include "LuaGlobalTime.h"
#include "LuaGlobalInput.h"
#include "LuaGlobalECS.h"

class GameStartEvent;

class IEScriptEngine : public IEObject
{
    sol::state lua;

    LuaGlobalTime* globalTime;
    LuaGlobalInput* globalInput;
    LuaGlobalECS* globalECS;

public:
    IEScriptEngine(QObject* parent = nullptr);
    ~IEScriptEngine();

    void startup(const GameStartEvent& event);
    void shutdown();

    sol::state& getLua() { return lua; }

private:
    void addGlobalUserTypes();
};

