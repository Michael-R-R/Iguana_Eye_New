#include "IEScript.h"

IEScript::IEScript() :
    IEResource("", 0),
    env(), isValid(false)
{

}

IEScript::IEScript(const QString& path, const unsigned long long id) :
    IEResource(path, id),
    env(), isValid(false)
{

}

IEScript::~IEScript()
{

}

sol::object IEScript::value(const char* name) const
{
    return env[name];
}

sol::object IEScript::getFunc(const char* name) const
{
    return env[name];
}

sol::object IEScript::callFunc(const char* name, sol::variadic_args args) const
{
    return env[name](args);
}
