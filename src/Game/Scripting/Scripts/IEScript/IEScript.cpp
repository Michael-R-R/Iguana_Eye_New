#include "IEScript.h"

IEScript::IEScript() :
    IEResource("", 0),
    env(), scriptData()
{

}

IEScript::IEScript(const QString& path, const unsigned long long id) :
    IEResource(path, id),
    env(), scriptData()
{

}

IEScript::~IEScript()
{

}

void IEScript::dataFromScript()
{
    scriptData.fromScript(env);
}

void IEScript::dataToScript()
{
    scriptData.toScript(env);
}

sol::object IEScript::value(const char* name)
{
    return env[name];
}

sol::object IEScript::func(const char* name, sol::variadic_args args)
{
    return env[name](args);
}
