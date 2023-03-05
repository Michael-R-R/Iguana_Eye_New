#pragma once

#include <QJSEngine>

#include "IEObject.h"

class GameStartEvent;
class IEGlobalTimeScript;

// TODO test
#include "IEScript.h"

class IEScriptEngine : public IEObject
{
    QJSEngine* engine;

    IEGlobalTimeScript* globalTime;

    // TODO test
    IEScript script;

public:
    IEScriptEngine(QObject* parent = nullptr);
    ~IEScriptEngine();

    void startup(const GameStartEvent& event);
    void shutdown();

    void onUpdateFrame();
};

