#pragma once

#include <QVector3D>

#include "IECamera.h"

class IEInput;

class ECamera : public IECamera
{
    QVector3D position;
    QVector3D rotation;

    float lastX;
    float lastY;
    bool isCaptured;

    float yaw;
    float pitch;

public:
    ECamera(QObject* parent = nullptr);
    ~ECamera();

    void update(IEInput* input, const float dt);
    void updateProjection(const float w, const float h);

    const QVector3D& getPosition() const { return position; }
    const QVector3D& getRotation() const { return rotation; }

private:
    void updateMovement(IEInput* input, const float dt);
    void updateRotation(IEInput* input, const float dt);

public:
    QDataStream& serialize(QDataStream &out, const Serializable &obj) const override;
    QDataStream& deserialize(QDataStream &in, Serializable &obj) override;
};

