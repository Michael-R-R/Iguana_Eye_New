#pragma once

#include "IEObject.h"

class GameStartEvent;
class IEGlobalTimeScript;
class IEGlobalInputScript;
class IEECSScriptSystem;

class IEScriptEngine : public IEObject
{
    IEGlobalTimeScript* globalTime;
    IEGlobalInputScript* globalInput;

    // DOES NOT OWN THIS POINTER
    IEECSScriptSystem* scriptSystem;

public:
    IEScriptEngine(QObject* parent = nullptr);
    ~IEScriptEngine();

    void startup(const GameStartEvent& event);
    void shutdown();

    void importScripts();
    void enableScripts();
    void disableScripts();

    IEGlobalTimeScript* getGlobalTime() const { return globalTime; }
    IEGlobalInputScript* getGlobalInput() const { return globalInput; }
};

