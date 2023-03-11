#include "IEEntityScript.h"
#include <QDebug>

IEEntityScript::IEEntityScript() :
    IEScript(),
    startFunc(), updateFunc(), wakeFunc(), sleepFunc(), scriptData()
{

}

IEEntityScript::IEEntityScript(const QString& path, const unsigned long long id) :
    IEScript(path, id),
    startFunc(), updateFunc(), wakeFunc(), sleepFunc(), scriptData()
{

}

IEEntityScript::~IEEntityScript()
{

}

bool IEEntityScript::initalize(sol::state& lua)
{
    env = sol::environment(lua, sol::create, lua.globals());

    try
    {
        lua.script_file(filePath.toStdString(), env);

        startFunc = env["start"];
        updateFunc = env["update"];
        wakeFunc = env["wake"];
        sleepFunc = env["sleep"];

        isValid = true;
    }
    catch(const std::exception& e)
    {
        isValid = false;

        qDebug() << QString("ERROR::%1").arg(e.what());
    }

    return isValid;
}

void IEEntityScript::start(const IEEntity entity)
{
    startFunc(entity);
}

void IEEntityScript::update()
{
    updateFunc();
}

void IEEntityScript::wake()
{
    wakeFunc();
}

void IEEntityScript::sleep()
{
    sleepFunc();
}

void IEEntityScript::dataFromScript()
{
    if(!isValid)
        return;

    scriptData.fromScript(env);
}

void IEEntityScript::dataToScript()
{
    if(!isValid)
        return;

    scriptData.toScript(env);
}
