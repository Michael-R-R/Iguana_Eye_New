#include "IECamera.h"

IECamera::IECamera() :
    IEResource("", 0),
    projection(), view(), up(),
    nearPlane(0.0f), farPlane(0.0f), fov(0.0f),
    speed(0.0f), sensitivity(0.0f)
{

}

IECamera::IECamera(const QString& path, const unsigned long long resourceId) :
    IEResource(path, resourceId),
    projection(), view(),
    up(0.0f, 1.0f, 0.0f),
    nearPlane(0.1f), farPlane(4000.0f), fov(75.0f),
    speed(15.0f), sensitivity(25.0f)
{

}

IECamera::IECamera(const IECamera& other) :
    IEResource(other.filePath, other.id),
    projection(other.projection), view(other.view),
    up(other.up),
    nearPlane(other.nearPlane), farPlane(other.farPlane), fov(other.fov),
    speed(other.speed), sensitivity(other.sensitivity)
{

}

void IECamera::updateView(const QVector3D& position, const QVector3D& rotation)
{
    view.setToIdentity();
    view.lookAt(position, rotation, up);
}
