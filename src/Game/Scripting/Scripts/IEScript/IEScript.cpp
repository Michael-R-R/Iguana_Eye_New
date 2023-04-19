#include "IEScript.h"

IEScript::IEScript(QObject* parent) :
    IEResource(parent),
    env()
{

}

IEScript::IEScript(const QString& path, QObject* parent) :
    IEResource(path, parent),
    env()
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

QDataStream& IEScript::serialize(QDataStream& out, const Serializable& obj) const
{
    return IEResource::serialize(out, obj);
}

QDataStream& IEScript::deserialize(QDataStream& in, Serializable& obj)
{
    return IEResource::deserialize(in, obj);
}
