#include "LuaGlobalInput.h"
#include "IEInput.h"

LuaGlobalInput::LuaGlobalInput(IEInput& val, sol::table& gameTable) :
    input(val)
{
    gameTable["IEInput"] = this;
    gameTable.new_usertype<LuaGlobalInput>("", sol::constructors<>(),
                                           "isPressed", &LuaGlobalInput::isPressed);
}

LuaGlobalInput::~LuaGlobalInput()
{

}

bool LuaGlobalInput::isPressed(const char* keyName)
{
    return input.isPressed(keyName);
}

