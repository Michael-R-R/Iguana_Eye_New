#pragma once

#include "IECamera.h"

class IEInput;

class ECamera : public IECamera
{
    glm::vec3 position;
    glm::vec3 rotation;

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

    const glm::vec3& getPosition() const { return position; }
    const glm::vec3& getRotation() const { return rotation; }

private:
    void updateMovement(IEInput* input, const float dt);
    void updateRotation(IEInput* input, const float dt);

public:
    QDataStream& serialize(QDataStream &out, const IESerializable &obj) const override;
    QDataStream& deserialize(QDataStream &in, IESerializable &obj) override;
};

