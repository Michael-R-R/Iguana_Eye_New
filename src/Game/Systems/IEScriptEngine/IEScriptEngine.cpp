#include "IEScriptEngine.h"
#include "IEGame.h"
#include "IETime.h"
#include "IEInput.h"
#include "IEECS.h"
#include "LuaEnum.h"
#include "LuaCommonType.h"
#include "LuaUtility.h"
#include "LuaApplication.h"
#include "LuaIETime.h"
#include "LuaIEInput.h"
#include "LuaIEECS.h"

IEScriptEngine::IEScriptEngine(QObject* parent) :
    IEGameSystem(parent),
    lua()
{

}

IEScriptEngine::~IEScriptEngine()
{

}

void IEScriptEngine::startup(IEGame& game)
{
    lua.open_libraries(sol::lib::base, sol::lib::math);

    // Create namespaces
    auto enumTable = lua["enum"].get_or_create<sol::table>();
    auto utilTable = lua["util"].get_or_create<sol::table>();
    auto gameTable = lua["game"].get_or_create<sol::table>();

    LuaCommonType::addToLua(lua);
    LuaEnum::addToLua(enumTable);
    LuaUtility::addToLua(utilTable);
    LuaApplication::addToLua(gameTable);
    LuaIETime::addToLua(game.getTime(), gameTable);
    LuaIEInput::addToLua(game.getInput(), gameTable);
    LuaIEECS::addToLua(game.getECS(), lua, gameTable);
}

void IEScriptEngine::shutdown(IEGame&)
{
    lua = nullptr;
}

void IEScriptEngine::onSerialize(IEGame&)
{

}

void IEScriptEngine::onDeserialize(IEGame& game)
{
    shutdown(game);
    startup(game);
}
