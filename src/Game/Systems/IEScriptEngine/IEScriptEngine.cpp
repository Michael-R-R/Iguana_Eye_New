#include "IEScriptEngine.h"
#include "GameStartEvent.h"
#include "IEScene.h"
#include "LuaEnum.h"
#include "LuaCommonType.h"
#include "LuaUtility.h"
#include "LuaIEEntity.h"
#include "LuaIEScript.h"
#include "LuaIETime.h"
#include "LuaIEInput.h"
#include "LuaIEECS.h"
#include "LuaIEECSScriptSystem.h"
#include "LuaIEECSTransformSystem.h"

IEScriptEngine::IEScriptEngine() :
    IEObject(),
    lua(),
    luaEnum(nullptr), luaCommonType(nullptr), luaUtility(nullptr), luaEntity(nullptr),
    luaScript(nullptr), luaTime(nullptr), luaInput(nullptr),
    luaECS(nullptr), luaScriptSystem(nullptr), luaTransformSystem(nullptr)
{

}

IEScriptEngine::~IEScriptEngine()
{

}

void IEScriptEngine::startup(const GameStartEvent& event)
{
    lua.open_libraries(sol::lib::base);

    // Create namespaces
    auto enumTable = lua["enum"].get_or_create<sol::table>();
    auto utilityTable = lua["util"].get_or_create<sol::table>();
    auto gameTable = lua["game"].get_or_create<sol::table>();

    luaEnum = std::make_unique<LuaEnum>(enumTable);
    luaCommonType = std::make_unique<LuaCommonType>(lua);
    luaUtility = std::make_unique<LuaUtility>(utilityTable);
    luaEntity = std::make_unique<LuaIEEntity>(lua);
    luaScript = std::make_unique<LuaIEScript>(lua);
    luaTime = std::make_unique<LuaIETime>(event.getTime(), gameTable);
    luaInput = std::make_unique<LuaIEInput>(event.getInput(), gameTable);
    luaECS = std::make_unique<LuaIEECS>(event.getScene().getECS(), gameTable);
    luaScriptSystem = std::make_unique<LuaIEECSScriptSystem>(lua);
    luaTransformSystem = std::make_unique<LuaIEECSTransformSystem>(lua);
}

void IEScriptEngine::shutdown()
{

}
