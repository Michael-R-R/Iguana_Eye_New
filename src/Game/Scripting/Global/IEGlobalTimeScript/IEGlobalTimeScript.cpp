#include "IEGlobalTimeScript.h"
#include "IETime.h"

IEGlobalTimeScript::IEGlobalTimeScript() :
    QObject(),
    time(nullptr)
{

}

IEGlobalTimeScript::IEGlobalTimeScript(IETime* val, sol::table& globalTable,  QObject* parent) :
    QObject(parent),
    time(val)
{
    globalTable["IETime"] = this;
    globalTable.new_usertype<IEGlobalTimeScript>("", sol::constructors<>(),
                                                 "fps", &IEGlobalTimeScript::fps,
                                                 "deltaTime", &IEGlobalTimeScript::deltaTime);
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
