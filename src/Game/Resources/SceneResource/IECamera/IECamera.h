#pragma once

#include <QVector3D>
#include <QMatrix4x4>

#include "IESceneResource.h"

class IECamera : public IESceneResource
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
    IECamera(QObject* parent = nullptr);
    IECamera(const QString& path, QObject* parent = nullptr);
    IECamera(const IECamera&) = delete;
    virtual ~IECamera();

    bool operator==(const IECamera& other) { return IEResource::operator==(other); }
    bool operator!=(const IECamera& other) { return IEResource::operator!=(other); }
    bool operator<(const IECamera& other) { return IEResource::operator<(other); }
    bool operator>(const IECamera& other) { return IEResource::operator>(other); }

    void updateView(const QVector3D& position, const QVector3D& rotation);

    QMatrix4x4 getViewProjection() const { return (projection * view); }
    const QMatrix4x4& getProjection() const { return projection; }
    const QMatrix4x4& getView() const { return view; }
    const QVector3D& getUp() const { return up; }
    float getNearPlane() { return nearPlane; }
    float getFarPlane() { return farPlane; }
    float getFOV() { return fov; }
    float getSpeed() { return speed; }
    float getSensitivity() { return sensitivity; }

    void setProjection(const QMatrix4x4& val) { projection = val; }
    void setNearPlane(const float val) { nearPlane = val; }
    void setFarPlane(const float val) { farPlane = val; }
    void setFOV(const float val) { fov = val; }
    void setSpeed(const float val) { speed = val; }
    void setSensitivity(const float val) { sensitivity = val; }

    QDataStream& serialize(QDataStream &out, const Serializable &obj) const override;
    QDataStream& deserialize(QDataStream &in, Serializable &obj) override;
};

