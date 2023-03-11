#pragma once

#include <sol/sol.hpp>

#include "IEObject.h"
#include "IEGlobalTimeScript.h"
#include "IEGlobalInputScript.h"
#include "IEGlobalECSScript.h"

class GameStartEvent;

class IEScriptEngine : public IEObject
{
    sol::state lua;

    IEGlobalTimeScript* globalTime;
    IEGlobalInputScript* globalInput;
    IEGlobalECSScript* globalECS;

public:
    IEScriptEngine(QObject* parent = nullptr);
    ~IEScriptEngine();

    void startup(const GameStartEvent& event);
    void shutdown();

    sol::state& getLua() { return lua; }

private:
    void addGlobalUserTypes();
};

