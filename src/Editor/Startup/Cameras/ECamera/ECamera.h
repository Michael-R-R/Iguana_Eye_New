#pragma once

#include <QVector3D>
#include <QVector4D>
#include <QMatrix4x4>

#include "IECamera.h"

class IEInput;

class ECamera : public IECamera
{
    QVector3D position;
    QVector3D rotation;
    QMatrix4x4 transform;

    float lastX;
    float lastY;
    bool isCaptured;

    float yaw;
    float pitch;

public:
    ECamera();
    ~ECamera();

    void update(IEInput& input, const float dt);
    void resize(const float w, const float h);

private:
    void updateMovement(IEInput& input, const float dt);
    void updateRotation(IEInput& input, const float dt);
    void calcModelMatrix();
};

