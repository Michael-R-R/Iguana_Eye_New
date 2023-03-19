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

IEScriptEngine::IEScriptEngine() :
    IEObject(),
    lua()
{

}

IEScriptEngine::~IEScriptEngine()
{

}

void IEScriptEngine::startup(const GameStartEvent& event)
{
    lua.open_libraries(sol::lib::base, sol::lib::math);

    // Create namespaces
    auto enumTable = lua["enum"].get_or_create<sol::table>();
    auto utilTable = lua["util"].get_or_create<sol::table>();
    auto gameTable = lua["game"].get_or_create<sol::table>();

    LuaCommonType::addToLua(lua);
    LuaEnum::addToLua(enumTable);
    LuaUtility::addToLua(utilTable);
    LuaApplication::addToLua(&event.getGame(), gameTable);
    LuaIETime::addToLua(&event.getTime(), gameTable);
    LuaIEInput::addToLua(&event.getInput(), gameTable);
    LuaIEECS::addToLua(&event.getScene().getECS(), lua, gameTable);
}

void IEScriptEngine::shutdown()
{

}
