#include "IEGlobalTimeScript.h"
#include "IETime.h"

IEGlobalTimeScript::IEGlobalTimeScript(IETime* val, QObject* parent) :
    QObject(parent),
    time(val)
{

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
