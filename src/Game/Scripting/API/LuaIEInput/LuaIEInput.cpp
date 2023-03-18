#include "LuaIEInput.h"
#include "IEInput.h"

LuaIEInput::LuaIEInput(IEInput& val, sol::table& gameTable)
{
    gameTable["IEInput"] = &val;
    gameTable.new_usertype<IEInput>("", sol::no_constructor,
                                    "isPressed", sol::resolve<const char*>(&IEInput::isPressed),
                                    "cursorPos", &IEInput::cursorPos,
                                    "wheelDelta", &IEInput::wheelDelta);
}

LuaIEInput::~LuaIEInput()
{

}

