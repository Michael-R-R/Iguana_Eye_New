#include "IEEntityScript.h"

IEEntityScript::IEEntityScript() :
    IEScript(),
    startFunc(), updateFunc(), sleepFunc()
{

}

IEEntityScript::IEEntityScript(const QString& path, const unsigned long long id) :
    IEScript(path, id),
    startFunc(), updateFunc(), sleepFunc()
{

}

IEEntityScript::~IEEntityScript()
{

}

void IEEntityScript::create(sol::state& lua)
{
    if(filePath.isEmpty())
        return;

    env = sol::environment(lua, sol::create, lua.globals());
    lua.script_file(filePath.toStdString(), env);

    startFunc = env["start"];
    updateFunc = env["update"];
    sleepFunc = env["sleep"];
}

void IEEntityScript::start(const int id)
{
    startFunc(id);
}

void IEEntityScript::update(const int id)
{
    updateFunc(id);
}

void IEEntityScript::sleep(const int id)
{
    sleepFunc(id);
}
