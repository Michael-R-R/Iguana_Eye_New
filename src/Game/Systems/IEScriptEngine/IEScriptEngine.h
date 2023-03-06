#pragma once

#include <QJSEngine>

#include "IEObject.h"

class GameStartEvent;
class IEGlobalTimeScript;
class IEGlobalInputScript;
class IEECSScriptSystem;

class IEScriptEngine : public IEObject
{
    QJSEngine* engine;

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

private:
    void setupGlobals(const GameStartEvent& event);
    void setupLocals();
    void setupExtensions();
};

