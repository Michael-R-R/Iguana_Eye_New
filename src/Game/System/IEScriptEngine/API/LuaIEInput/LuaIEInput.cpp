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
                                    "cursorPos", &LuaIEInput::cursorPos);
}

bool LuaIEInput::isPressed(const char* key)
{
    return input->isPressed(key);
}

const glm::vec2& LuaIEInput::cursorPos() const
{
    return input->cursorPos();
}

