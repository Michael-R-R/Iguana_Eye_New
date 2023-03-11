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

sol::object IEScript::value(const char* name)
{
    return env[name];
}

sol::object IEScript::func(const char* name, sol::variadic_args args)
{
    return env[name](args);
}
