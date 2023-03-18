#include "IEScriptEngine.h"
#include "GameStartEvent.h"
#include "IEScene.h"
#include "LuaEnum.h"
#include "LuaCommonType.h"
#include "LuaUtility.h"
#include "LuaApplication.h"
#include "LuaIETime.h"
#include "LuaIEInput.h"
#include "LuaIEECS.h"
#include "LuaIEECSInputSystem.h"
#include "LuaIEECSScriptSystem.h"
#include "LuaIEECSTransformSystem.h"
#include "LuaIEECSCameraSystem.h"

IEScriptEngine::IEScriptEngine() :
    IEObject(),
    lua(),
    luaEnum(nullptr), luaCommonType(nullptr), luaUtility(nullptr), luaApplication(nullptr),
    luaTime(nullptr), luaInput(nullptr), luaECS(nullptr),
    luaInputSystem(nullptr), luaScriptSystem(nullptr), luaTransformSystem(nullptr),
    luaCameraSystem(nullptr)
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
    luaApplication = std::make_unique<LuaApplication>(event.getGame(), gameTable);
    luaTime = std::make_unique<LuaIETime>(event.getTime(), gameTable);
    luaInput = std::make_unique<LuaIEInput>(event.getInput(), gameTable);
    luaECS = std::make_unique<LuaIEECS>(event.getScene().getECS(), lua, gameTable);
    luaInputSystem = std::make_unique<LuaIEECSInputSystem>(lua);
    luaScriptSystem = std::make_unique<LuaIEECSScriptSystem>(lua);
    luaTransformSystem = std::make_unique<LuaIEECSTransformSystem>(lua);
    luaCameraSystem = std::make_unique<LuaIEECSCameraSystem>(lua);
}

void IEScriptEngine::shutdown()
{

}
