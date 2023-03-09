#pragma once

#include <sol/sol.hpp>

#include "IEObject.h"

class GameStartEvent;
class IEGlobalTimeScript;
class IEGlobalInputScript;

class IEScriptEngine : public IEObject
{
    sol::state lua;

    IEGlobalTimeScript* globalTime;
    IEGlobalInputScript* globalInput;

public:
    IEScriptEngine(QObject* parent = nullptr);
    ~IEScriptEngine();

    void startup(const GameStartEvent& event);
    void shutdown();

    IEGlobalTimeScript* getGlobalTime() const { return globalTime; }
    IEGlobalInputScript* getGlobalInput() const { return globalInput; }
};

