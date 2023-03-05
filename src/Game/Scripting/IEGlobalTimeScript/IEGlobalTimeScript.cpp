#include "IEGlobalTimeScript.h"
#include "GameStartEvent.h"
#include "IETime.h"

IEGlobalTimeScript::IEGlobalTimeScript(const GameStartEvent& event, QObject* parent) :
    QObject(parent),
    time(nullptr)
{
    time = event.getTime();
}

IEGlobalTimeScript::~IEGlobalTimeScript()
{
    time = nullptr;
}

float IEGlobalTimeScript::fps()
{
    return time->getFPS();
}

float IEGlobalTimeScript::deltaTime()
{
    return time->getDeltaTime();
}
