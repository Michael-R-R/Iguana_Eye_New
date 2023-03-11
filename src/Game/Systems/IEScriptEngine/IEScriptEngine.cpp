#include "IEScriptEngine.h"
#include "GameStartEvent.h"
#include "IEScene.h"

IEScriptEngine::IEScriptEngine(QObject* parent) :
    IEObject(parent),
    lua(), globalTime(nullptr), globalInput(nullptr), globalECS(nullptr)
{

}

IEScriptEngine::~IEScriptEngine()
{
    delete globalTime;
    delete globalInput;
    delete globalECS;
}

void IEScriptEngine::startup(const GameStartEvent& event)
{
    lua.open_libraries(sol::lib::base);

    addGlobalUserTypes();

    // Create namespaces
    auto gameTable = lua["game"].get_or_create<sol::table>();

    globalTime = new IEGlobalTimeScript(event.getTime(), gameTable);
    globalInput = new IEGlobalInputScript(event.getInput(), gameTable);
    globalECS = new IEGlobalECSScript(event.getScene()->getECS(), gameTable);
}

void IEScriptEngine::shutdown()
{

}

void IEScriptEngine::addGlobalUserTypes()
{
    lua.new_usertype<IEScript>("", sol::constructors<>(),
                               "value", &IEScript::value,
                               "func", &IEScript::func);
}


