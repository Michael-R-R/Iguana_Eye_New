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
    lua.open_libraries(sol::lib::base, sol::lib::package);

    // Make Lua namespaces
    auto globalTable = lua["global"].get_or_create<sol::table>();

    globalTime = new IEGlobalTimeScript(event.getTime(), globalTable, this);
    globalInput = new IEGlobalInputScript(event.getInput(), this);

    // TODO test
    lua.script_file("./resources/scripts/test/test1.lua");
    lua["add"]();
    lua["printNum"]();
}

void IEScriptEngine::shutdown()
{

}


