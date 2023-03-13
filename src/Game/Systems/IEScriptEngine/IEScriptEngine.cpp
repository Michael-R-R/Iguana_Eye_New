#include "IEScriptEngine.h"
#include "GameStartEvent.h"
#include "IEScene.h"
#include "LuaGlobalType.h"
#include "LuaGlobalEnum.h"
#include "LuaGlobalTime.h"
#include "LuaGlobalInput.h"
#include "LuaGlobalECS.h"

IEScriptEngine::IEScriptEngine() :
    IEObject(),
    lua(),
    globalType(nullptr), globalEnum(nullptr),
    globalTime(nullptr), globalInput(nullptr),
    globalECS(nullptr)
{

}

IEScriptEngine::~IEScriptEngine()
{

}

void IEScriptEngine::startup(const GameStartEvent& event)
{
    lua.open_libraries(sol::lib::base);

    // Create namespaces
    auto gameTable = lua["game"].get_or_create<sol::table>();
    auto enumTable = lua["enum"].get_or_create<sol::table>();

    globalType = std::make_unique<LuaGlobalType>(lua);
    globalEnum = std::make_unique<LuaGlobalEnum>(enumTable);
    globalTime = std::make_unique<LuaGlobalTime>(event.getTime(), gameTable);
    globalInput = std::make_unique<LuaGlobalInput>(event.getInput(), gameTable);
    globalECS = std::make_unique<LuaGlobalECS>(event.getScene().getECS(), gameTable);
}

void IEScriptEngine::shutdown()
{

}
