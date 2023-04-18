#include "IECameraScript.h"
#include "IECamera.h"
#include <QDebug>

IECameraScript::IECameraScript() :
    IEScript(),
    startFunc(), updateFunc(), updateProjectionFunc()
{

}

IECameraScript::IECameraScript(const QString& path) :
    IEScript(path),
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

        return true;
    }
    catch(const std::exception& e)
    {
        qDebug() << QString("ERROR::%1").arg(e.what());

        return false;
    }
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
    return IEScript::serialize(out, obj);
}

QDataStream& IECameraScript::deserialize(QDataStream& in, Serializable& obj)
{
    return IEScript::deserialize(in, obj);
}
