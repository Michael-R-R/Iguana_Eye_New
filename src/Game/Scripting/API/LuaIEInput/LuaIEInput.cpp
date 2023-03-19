#include "LuaIEInput.h"
#include "IEInput.h"

LuaIEInput LuaIEInput::instance;

LuaIEInput::LuaIEInput() :
    input(nullptr)
{

}

LuaIEInput::~LuaIEInput()
{
    input = nullptr;
}

void LuaIEInput::addToLua(IEInput* val, sol::table& gameTable)
{
    instance.input = val;

    gameTable["IEInput"] = instance;
    gameTable.new_usertype<LuaIEInput>("", sol::no_constructor,
                                    "isPressed", &LuaIEInput::isPressed,
                                    "getCursorPos", &LuaIEInput::cursorPos,
                                    "getWheelDelta", &LuaIEInput::wheelDelta);
}

bool LuaIEInput::isPressed(const char* key)
{
    return input->isPressed(key);
}

QVector2D LuaIEInput::cursorPos()
{
    return input->cursorPos();
}

QVector2D LuaIEInput::wheelDelta()
{
    return input->wheelDelta();
}

