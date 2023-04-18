#include "IECamera.h"

IECamera::IECamera(QObject* parent) :
    IEResource(parent),
    projection(), view(),
    up(0.0f, 1.0f, 0.0f),
    nearPlane(0.1f), farPlane(4000.0f), fov(75.0f),
    speed(15.0f), sensitivity(25.0f)
{

}

IECamera::IECamera(const QString& path, QObject* parent) :
    IEResource(path, parent),
    projection(), view(),
    up(0.0f, 1.0f, 0.0f),
    nearPlane(0.1f), farPlane(4000.0f), fov(75.0f),
    speed(15.0f), sensitivity(25.0f)
{

}

IECamera::~IECamera()
{

}

void IECamera::updateView(const QVector3D& position, const QVector3D& rotation)
{
    view.setToIdentity();
    view.lookAt(position, position + rotation, up);
}

QDataStream& IECamera::serialize(QDataStream& out, const Serializable& obj) const
{
    IEResource::serialize(out, obj);

    const auto& camera = static_cast<const IECamera&>(obj);

    out << camera.projection << camera.view
        << camera.up << camera.nearPlane
        << camera.farPlane << camera.fov
        << camera.speed << camera.sensitivity;

    return out;
}

QDataStream& IECamera::deserialize(QDataStream& in, Serializable& obj)
{
    IEResource::deserialize(in, obj);

    auto& camera = static_cast<IECamera&>(obj);

    in >> camera.projection >> camera.view
       >> camera.up >> camera.nearPlane
       >> camera.farPlane >> camera.fov
       >> camera.speed >> camera.sensitivity;

    return in;
}
