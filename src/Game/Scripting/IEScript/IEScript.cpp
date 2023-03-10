#include "IEScript.h"

IEScript::IEScript() :
    IEResource("", 0),
    env(), startFunc(), updateFunc(), sleepFunc(), scriptData()
{

}

IEScript::IEScript(const QString& path, const unsigned long long id) :
    IEResource(path, id),
    env(), startFunc(), updateFunc(), sleepFunc(), scriptData()
{

}

IEScript::IEScript(const IEScript& other) :
    IEResource(other.filePath, other.id),
    env(other.env), startFunc(other.startFunc), updateFunc(other.updateFunc),
    sleepFunc(other.sleepFunc), scriptData(other.scriptData)
{

}

IEScript::~IEScript()
{

}

void IEScript::create(sol::state& lua)
{
    if(filePath.isEmpty())
        return;

    env = sol::environment(lua, sol::create, lua.globals());
    lua.script_file(filePath.toStdString(), env);

    startFunc = env["start"];
    updateFunc = env["update"];
    sleepFunc = env["sleep"];
}

void IEScript::start(const int id)
{
    startFunc(id);
}

void IEScript::update(const int id)
{
    updateFunc(id);
}

void IEScript::sleep(const int id)
{
    sleepFunc(id);
}

sol::object IEScript::value(const char* name)
{
    return env[name];
}

sol::object IEScript::func(const char* name, sol::variadic_args args)
{
    return env[name](args);
}
