#include "IEScript.h"
#include "IEEntity.h"
#include <QDebug>

IEScript::IEScript(QObject* parent) :
    IEFileResource(parent),
    env(), initFunc(), startFunc(), updateFunc(),
    wakeFunc(), sleepFunc(),
    onTriggerEnterFunc(), onTriggerLeaveFunc(),
    scriptData()
{

}

IEScript::IEScript(const QString& path, QObject* parent) :
    IEFileResource(path, parent),
    env(), initFunc(), startFunc(), updateFunc(),
    wakeFunc(), sleepFunc(),
    onTriggerEnterFunc(), onTriggerLeaveFunc(),
    scriptData()
{

}

IEScript::~IEScript()
{

}

bool IEScript::init(sol::state& lua, const IEEntity& entity)
{
    env = sol::environment(lua, sol::create, lua.globals());

    try
    {
        lua.script_file(name.toStdString(), env);

        initFunc = env["init"];
        startFunc = env["start"];
        updateFunc = env["update"];
        wakeFunc = env["wake"];
        sleepFunc = env["sleep"];
        onTriggerEnterFunc = env["onTriggerEnter"];
        onTriggerLeaveFunc = env["onTriggerLeave"];

        initFunc(entity);

        return true;
    }
    catch(const std::exception& e)
    {
        qDebug() << QString("ERROR::%1").arg(e.what());

        return false;
    }
}

void IEScript::start()
{
    startFunc();
}

void IEScript::update()
{
    updateFunc();
}

void IEScript::wake()
{
    wakeFunc();
}

void IEScript::sleep()
{
    sleepFunc();
}

void IEScript::onTriggerEnter(const IEEntity& other)
{
    onTriggerEnterFunc(other);
}

void IEScript::onTriggerLeave(const IEEntity& other)
{
    onTriggerLeaveFunc(other);
}

void IEScript::dataFrom()
{
    if(!env)
        return;

    scriptData.fromScript(env);
}

void IEScript::dataTo()
{
    if(!env)
        return;

    scriptData.toScript(env);
}

sol::function IEScript::getCustomFunc(const char* name) const
{
    return env[name];
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

QDataStream& IEScript::serialize(QDataStream& out, const IESerializable& obj) const
{
    IEFileResource::serialize(out, obj);

    const auto& script = static_cast<const IEScript&>(obj);

    out << script.scriptData;

    return out;
}

QDataStream& IEScript::deserialize(QDataStream& in, IESerializable& obj)
{
    IEFileResource::deserialize(in, obj);

    auto& script = static_cast<IEScript&>(obj);

    in >> script.scriptData;

    return in;
}
