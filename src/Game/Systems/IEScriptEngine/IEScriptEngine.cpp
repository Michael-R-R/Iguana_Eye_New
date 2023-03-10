#include "IEScriptEngine.h"
#include "GameStartEvent.h"
#include "IEScene.h"
#include "IEGlobalTimeScript.h"
#include "IEGlobalInputScript.h"

IEScriptEngine::IEScriptEngine(QObject* parent) :
    IEObject(parent),
    lua(),
    globalTime(nullptr), globalInput(nullptr)
{

}

IEScriptEngine::~IEScriptEngine()
{

}

void IEScriptEngine::startup(const GameStartEvent& event)
{
    lua.open_libraries(sol::lib::base);

    // Make Lua namespaces
    auto globalTable = lua["global"].get_or_create<sol::table>();

    globalTime = new IEGlobalTimeScript(event.getTime(), globalTable, this);
    globalInput = new IEGlobalInputScript(event.getInput(), globalTable, this);
}

void IEScriptEngine::shutdown()
{

}


