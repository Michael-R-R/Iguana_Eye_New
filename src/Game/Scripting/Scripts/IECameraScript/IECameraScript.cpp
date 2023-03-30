#include "IECameraScript.h"
#include "IECamera.h"
#include <QDebug>

IECameraScript::IECameraScript() :
    IEScript(),
    startFunc(), updateFunc(), updateProjectionFunc()
{

}

IECameraScript::IECameraScript(const QString& path, const unsigned long long id) :
    IEScript(path, id),
    startFunc(), updateFunc(), updateProjectionFunc()
{

}

IECameraScript::~IECameraScript()
{

}

bool IECameraScript::initalize(sol::state& lua)
{
    env = sol::environment(lua, sol::create, lua.globals());

    try
    {
        lua.script_file(filePath.toStdString(), env);

        startFunc = env["start"];
        updateFunc = env["update"];
        updateProjectionFunc = env["updateProjection"];

        isValid = true;
    }
    catch(const std::exception& e)
    {
        isValid = false;

        qDebug() << QString("ERROR::%1").arg(e.what());
    }

    return isValid;
}

void IECameraScript::start(const IEEntity entity) const
{
    startFunc(entity);
}

void IECameraScript::update() const
{
    updateFunc();
}

void IECameraScript::updateProjection(IECamera* camera, const float w, const float h) const
{
    updateProjectionFunc(camera, w, h);
}

QDataStream& IECameraScript::serialize(QDataStream& out, const Serializable& obj) const
{
    const auto& script = static_cast<const IECameraScript&>(obj);

    out << script.filePath << script.id;

    return out;
}

QDataStream& IECameraScript::deserialize(QDataStream& in, Serializable& obj)
{
    auto& script = static_cast<IECameraScript&>(obj);

    in >> script.filePath >> script.id;

    return in;
}
