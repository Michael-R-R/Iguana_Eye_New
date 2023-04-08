#include "IEEntityScript.h"
#include <QDebug>

IEEntityScript::IEEntityScript() :
    IEScript(),
    startFunc(), updateFunc(),
    wakeFunc(), sleepFunc(),
    onTriggerEnterFunc(), onTriggerLeaveFunc(),
    scriptData()
{

}

IEEntityScript::IEEntityScript(const QString& path) :
    IEScript(path),
    startFunc(), updateFunc(),
    wakeFunc(), sleepFunc(),
    onTriggerEnterFunc(),
    onTriggerLeaveFunc(),
    scriptData()
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
        onTriggerEnterFunc = env["onTriggerEnter"];
        onTriggerLeaveFunc = env["onTriggerLeave"];

        return true;
    }
    catch(const std::exception& e)
    {
        qDebug() << QString("ERROR::%1").arg(e.what());

        return false;
    }
}

void IEEntityScript::start(const IEEntity entity) const
{
    startFunc(entity);
}

void IEEntityScript::update() const
{
    updateFunc();
}

void IEEntityScript::wake() const
{
    wakeFunc();
}

void IEEntityScript::sleep() const
{
    sleepFunc();
}

void IEEntityScript::onTriggerEnter(const IEEntity& otherEntity) const
{
    onTriggerEnterFunc(otherEntity);
}

void IEEntityScript::onTriggerLeave(const IEEntity& otherEntity) const
{
    onTriggerLeaveFunc(otherEntity);
}

void IEEntityScript::dataFromScript()
{
    scriptData.fromScript(env);
}

void IEEntityScript::dataToScript()
{
    scriptData.toScript(env);
}

QDataStream& IEEntityScript::serialize(QDataStream& out, const Serializable& obj) const
{
    IEScript::serialize(out, obj);

    const auto& script = static_cast<const IEEntityScript&>(obj);

    const_cast<IEEntityScript&>(script).dataFromScript();

    out << script.scriptData;

    return out;
}

QDataStream& IEEntityScript::deserialize(QDataStream& in, Serializable& obj)
{
    IEScript::deserialize(in, obj);

    auto& script = static_cast<IEEntityScript&>(obj);

    in >> script.scriptData;

    return in;
}
