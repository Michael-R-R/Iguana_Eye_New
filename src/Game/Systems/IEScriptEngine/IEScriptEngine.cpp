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

IEScriptEngine IEScriptEngine::mInstance;
IEScriptEngine& IEScriptEngine::instance() { return mInstance; }

IEScriptEngine::IEScriptEngine() :
    lua()
{

}

IEScriptEngine::~IEScriptEngine()
{

}

void IEScriptEngine::startup(IEGame&)
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
    LuaIETime::addToLua(&IETime::instance(), gameTable);
    LuaIEInput::addToLua(&IEInput::instance(), gameTable);
    LuaIEECS::addToLua(&IEECS::instance(), lua, gameTable);
}

void IEScriptEngine::shutdown(IEGame& game)
{
    lua = nullptr;
}

void IEScriptEngine::initalize(IEGame&)
{

}

void IEScriptEngine::reset(IEGame& game)
{
    shutdown(game);
    startup(game);
}
