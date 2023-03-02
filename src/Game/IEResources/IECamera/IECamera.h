#pragma once

#include <QDataStream>
#include <QVector3D>
#include <QMatrix4x4>

#include "IEResource.h"

class IECamera : public IEResource
{
protected:
    QMatrix4x4 projection;
    QMatrix4x4 view;
    QVector3D up;
    float nearPlane;
    float farPlane;
    float fov;
    float speed;
    float sensitivity;

public:
    IECamera();
    IECamera(const QString& path, const unsigned long long resourceId);
    IECamera(const IECamera& other);
    ~IECamera() {}

    bool operator==(const IECamera& other) { return IEResource::operator==(other); }
    bool operator!=(const IECamera& other) { return IEResource::operator!=(other); }
    bool operator<(const IECamera& other) { return IEResource::operator<(other); }
    bool operator>(const IECamera& other) { return IEResource::operator>(other); }

    virtual void updateProjection(int w, int h);
    virtual void updateView(const QVector3D& position, const QVector3D& rotation);

    const QMatrix4x4& getProjection() const { return projection; }
    const QMatrix4x4& getView() const { return view; }
    const QVector3D& getUp() const { return up; }
    float getNear() { return nearPlane; }
    float getFar() { return farPlane; }
    float getFOV() { return fov; }
    float getSpeed() { return speed; }
    float getSensitivity() { return sensitivity; }

    void setNear(const float val) { nearPlane = val; }
    void setFar(const float val) { farPlane = val; }
    void setFOV(const float val) { fov = val; }
    void setSpeed(const float val) { speed = val; }
    void setSensitivity(const float val) { sensitivity = val; }

    friend QDataStream& operator<<(QDataStream& out, const IECamera& camera)
    {
        out << camera.filePath << camera.id << camera.type
            << camera.projection << camera.view
            << camera.up << camera.nearPlane
            << camera.farPlane << camera.fov
            << camera.speed << camera.sensitivity;

        return out;
    }

    friend QDataStream& operator>>(QDataStream& in, IECamera& camera)
    {
        in >> camera.filePath >> camera.id >> camera.type
           >> camera.projection >> camera.view
           >> camera.up >> camera.nearPlane
           >> camera.farPlane >> camera.fov
           >> camera.speed >> camera.sensitivity;

        return in;
    }
};

