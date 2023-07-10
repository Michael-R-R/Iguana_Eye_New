#include "IECamera.h"
#include "IESerializeConverter.h"
#include <glm/gtc/matrix_transform.hpp>

IECamera::IECamera(QObject* parent) :
    IESceneResource(parent),
    projection(1.0f), view(1.0f),
    up(0.0f, 1.0f, 0.0f),
    nearPlane(0.1f), farPlane(4000.0f), fov(75.0f),
    speed(15.0f), sensitivity(0.25f)
{

}

IECamera::IECamera(const QString& path, QObject* parent) :
    IESceneResource(path, parent),
    projection(1.0f), view(1.0f),
    up(0.0f, 1.0f, 0.0f),
    nearPlane(0.1f), farPlane(4000.0f), fov(75.0f),
    speed(15.0f), sensitivity(0.25f)
{

}

IECamera::~IECamera()
{

}

void IECamera::updateView(const glm::vec3& position, const glm::vec3& rotation)
{
    view = glm::lookAt(position, position + rotation, up);
}

void IECamera::updateView(const glm::vec3& position, const glm::vec4& rotation)
{
    view = glm::lookAt(position, position + glm::vec3(rotation), up);
}

QDataStream& IECamera::serialize(QDataStream& out, const IESerializable& obj) const
{
    IESceneResource::serialize(out, obj);

    const auto& camera = static_cast<const IECamera&>(obj);

    IESerializeConverter::write(out, camera.up);

    out << camera.nearPlane
        << camera.farPlane
        << camera.fov
        << camera.speed
        << camera.sensitivity;

    return out;
}

QDataStream& IECamera::deserialize(QDataStream& in, IESerializable& obj)
{
    IESceneResource::deserialize(in, obj);

    auto& camera = static_cast<IECamera&>(obj);

    IESerializeConverter::read(in, camera.up);

    in >> camera.nearPlane
       >> camera.farPlane
       >> camera.fov
       >> camera.speed
       >> camera.sensitivity;

    return in;
}
