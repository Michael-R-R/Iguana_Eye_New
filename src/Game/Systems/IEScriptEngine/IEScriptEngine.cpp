#include "IEScriptEngine.h"
#include "GameStartEvent.h"
#include "IEScene.h"
#include "IEGlobalTimeScript.h"
#include "IEGlobalInputScript.h"

IEScriptEngine::IEScriptEngine(QObject* parent) :
    IEObject(parent),
    globalTime(nullptr), globalInput(nullptr),
    scriptSystem(nullptr)
{

}

IEScriptEngine::~IEScriptEngine()
{
    scriptSystem = nullptr;
}

void IEScriptEngine::startup(const GameStartEvent& event)
{
    globalTime = new IEGlobalTimeScript(event.getTime(), this);
    globalInput = new IEGlobalInputScript(event.getInput(), this);

    auto ecs = event.getScene()->getECS();
    scriptSystem = ecs->getComponent<IEECSScriptSystem>(IEComponentType::Script);
}

void IEScriptEngine::shutdown()
{

}

void IEScriptEngine::importScripts()
{
    scriptSystem->importAllScripts();
}

void IEScriptEngine::enableScripts()
{
    scriptSystem->enableAllScripts();
}

void IEScriptEngine::disableScripts()
{
    scriptSystem->disableAllScripts();
}
