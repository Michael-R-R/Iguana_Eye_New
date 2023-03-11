#include "IEGlobalInputScript.h"
#include "IEInput.h"

IEGlobalInputScript::IEGlobalInputScript(IEInput* val, sol::table& gameTable) :
    input(val)
{
    gameTable["IEInput"] = this;
    gameTable.new_usertype<IEGlobalInputScript>("", sol::constructors<>(),
                                                "isPressed", &IEGlobalInputScript::isPressed);
}

IEGlobalInputScript::~IEGlobalInputScript()
{
    input = nullptr;
}

bool IEGlobalInputScript::isPressed(const char* keyName)
{
    return input->isPressed(keyName);
}

