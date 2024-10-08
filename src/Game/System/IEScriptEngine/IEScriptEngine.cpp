#include "IEScriptEngine.h"
#include "IEGame.h"
#include "IEScene.h"
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
    IESystem(parent),
    lua()
{

}

IEScriptEngine::~IEScriptEngine()
{

}

void IEScriptEngine::startup(IEGame& game)
{
    auto* scene = game.getSystem<IEScene>();

    lua.open_libraries(sol::lib::base, sol::lib::math);

    // Create namespaces
    auto enumTable = lua["enum"].get_or_create<sol::table>();
    auto utilTable = lua["util"].get_or_create<sol::table>();
    auto gameTable = lua["game"].get_or_create<sol::table>();

    LuaCommonType::addToLua(lua);
    LuaEnum::addToLua(enumTable);
    LuaUtility::addToLua(utilTable);
    LuaApplication::addToLua(gameTable);
    LuaIETime::addToLua(game.getSystem<IETime>(), gameTable);
    LuaIEInput::addToLua(game.getSystem<IEInput>(), gameTable);
    LuaIEECS::addToLua(scene->getSystem<IEECS>(), lua, gameTable);
}

void IEScriptEngine::shutdown(IEGame&)
{
    lua = nullptr;
}
