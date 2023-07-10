#pragma once

#include <glm/glm.hpp>

#include "IESceneResource.h"
#include "GLSViewProjection.h"

class IECamera : public IESceneResource
{
protected:
    glm::mat4 projection;
    glm::mat4 view;
    glm::vec3 up;
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

    void updateView(const glm::vec3& position, const glm::vec3& rotation);
    void updateView(const glm::vec3& position, const glm::vec4& rotation);

    glm::mat4 getViewProjection() const { return (projection * view); }
    const glm::mat4& getProjection() const { return projection; }
    const glm::mat4& getView() const { return view; }
    const glm::vec3& getUp() const { return up; }
    float getNearPlane() const { return nearPlane; }
    float getFarPlane() const { return farPlane; }
    float getFOV() const { return fov; }
    float getSpeed() const { return speed; }
    float getSensitivity() const { return sensitivity; }
    GLSViewProjection getVPStruct() { return GLSViewProjection(view, projection); }

    void setProjection(const glm::mat4& val) { projection = val; }
    void setNearPlane(const float val) { nearPlane = val; }
    void setFarPlane(const float val) { farPlane = val; }
    void setFOV(const float val) { fov = val; }
    void setSpeed(const float val) { speed = val; }
    void setSensitivity(const float val) { sensitivity = val; }

    QDataStream& serialize(QDataStream &out, const IESerializable &obj) const override;
    QDataStream& deserialize(QDataStream &in, IESerializable &obj) override;
};

