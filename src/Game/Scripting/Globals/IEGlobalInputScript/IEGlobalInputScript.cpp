#include "IEGlobalInputScript.h"
#include "IEInput.h"

IEGlobalInputScript::IEGlobalInputScript(IEInput* val, sol::table& globalTable, QObject* parent) :
    QObject(parent),
    input(val)
{
    globalTable["IEInput"] = this;
    globalTable.new_usertype<IEGlobalInputScript>("", sol::constructors<>(),
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

