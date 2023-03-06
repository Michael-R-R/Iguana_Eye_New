#include "IEScriptEngine.h"
#include "GameStartEvent.h"
#include "IEGlobalTimeScript.h"
#include "IEGlobalInputScript.h"
#include "IELocalEntityScript.h"

IEScriptEngine::IEScriptEngine(QObject* parent) :
    IEObject(parent),
    engine(new QJSEngine(this)),
    globalTime(nullptr), globalInput(nullptr)
{

}

IEScriptEngine::~IEScriptEngine()
{

}

void IEScriptEngine::startup(const GameStartEvent& event)
{
    setupGlobals(event);
    setupLocals();
    setupExtensions();
}

void IEScriptEngine::shutdown()
{
    delete engine;
}

void IEScriptEngine::importScripts()
{
    // TODO fetch scripts and import them
}

void IEScriptEngine::setupGlobals(const GameStartEvent& event)
{
    globalTime = new IEGlobalTimeScript(event.getTime(), engine);
    globalInput = new IEGlobalInputScript(event.getInput(), engine);

    engine->globalObject().setProperty("IETime", engine->newQObject(globalTime));
    engine->globalObject().setProperty("IEInput", engine->newQObject(globalInput));
}

void IEScriptEngine::setupLocals()
{
    engine->globalObject().setProperty("Entity", engine->newQMetaObject(&IELocalEntityScript::staticMetaObject));
}

void IEScriptEngine::setupExtensions()
{
    engine->installExtensions(QJSEngine::ConsoleExtension);
}
