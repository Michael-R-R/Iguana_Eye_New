#include "IEScriptEngine.h"
#include "GameStartEvent.h"
#include "IEScene.h"
#include "IEScript.h"
#include "LuaGlobalTime.h"
#include "LuaGlobalInput.h"
#include "LuaGlobalECS.h"

IEScriptEngine::IEScriptEngine() :
    IEObject(),
    lua(), globalTime(nullptr), globalInput(nullptr), globalECS(nullptr)
{

}

IEScriptEngine::~IEScriptEngine()
{

}

void IEScriptEngine::startup(const GameStartEvent& event)
{
    lua.open_libraries(sol::lib::base);

    addGlobalUserTypes();

    // Create namespaces
    auto gameTable = lua["game"].get_or_create<sol::table>();

    globalTime = std::make_unique<LuaGlobalTime>(event.getTime(), gameTable);
    globalInput = std::make_unique<LuaGlobalInput>(event.getInput(), gameTable);
    globalECS = std::make_unique<LuaGlobalECS>(event.getScene().getECS(), gameTable);
}

void IEScriptEngine::shutdown()
{

}

void IEScriptEngine::addGlobalUserTypes()
{
    lua.new_usertype<IEScript>("", sol::constructors<>(),
                               "value", &IEScript::value,
                               "func", &IEScript::func);

    lua.new_usertype<IEEntity>("", sol::constructors<>(),
                               "id", sol::property(&IEEntity::getId));
}


