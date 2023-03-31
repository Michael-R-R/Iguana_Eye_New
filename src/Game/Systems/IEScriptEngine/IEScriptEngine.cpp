#include "IEScriptEngine.h"
#include "IEGame.h"
#include "LuaEnum.h"
#include "LuaCommonType.h"
#include "LuaUtility.h"
#include "LuaApplication.h"
#include "LuaIETime.h"
#include "LuaIEInput.h"
#include "LuaIEECS.h"

IEScriptEngine::IEScriptEngine(IEGame& game) :
    IEObject(),
    lua()
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
    LuaIETime::addToLua(&game.getIETime(), gameTable);
    LuaIEInput::addToLua(&game.getIEInput(), gameTable);
    LuaIEECS::addToLua(&game.getECS(), lua, gameTable);
}

IEScriptEngine::~IEScriptEngine()
{

}
