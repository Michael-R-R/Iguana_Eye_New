#include "IEGlobalTimeScript.h"
#include "IETime.h"

IEGlobalTimeScript::IEGlobalTimeScript(IETime* val, sol::table& gameTable) :
    time(val)
{
    gameTable["IETime"] = this;
    gameTable.new_usertype<IEGlobalTimeScript>("", sol::constructors<>(),
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
