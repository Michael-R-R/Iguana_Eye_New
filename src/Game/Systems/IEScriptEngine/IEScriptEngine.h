#pragma once

#include <QJSEngine>

#include "IEObject.h"

class GameStartEvent;
class IEGlobalTimeScript;
class IEGlobalInputScript;

// TODO test
#include "IEScript.h"

class IEScriptEngine : public IEObject
{
    QJSEngine* engine;

    IEGlobalTimeScript* globalTime;
    IEGlobalInputScript* globalInput;

    // TODO test
    IEScript script1;
    IEScript script2;

public:
    IEScriptEngine(QObject* parent = nullptr);
    ~IEScriptEngine();

    void startup(const GameStartEvent& event);
    void shutdown();

    void importScripts();

private:
    void setupGlobals(const GameStartEvent& event);
    void setupLocals();
    void setupExtensions();
};

