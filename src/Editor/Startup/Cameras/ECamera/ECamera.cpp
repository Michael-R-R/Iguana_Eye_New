#include "ECamera.h"
#include "IEInput.h"

ECamera::ECamera() :
    IECamera("", 0),
    position(0.0f, 5.0f, 0.0f), rotation(0.0f, 0.0f, -1.0f), transform(),
    lastX(0.0f), lastY(0.0f), isCaptured(false),
    yaw(-90.0f), pitch(0.0f)
{

}

ECamera::~ECamera()
{

}

void ECamera::update(IEInput& input, const float dt)
{
    updateMovement(input, dt);
    updateRotation(input, dt);
    updateView(position, rotation);
}

void ECamera::resize(const float w, const float h)
{
    projection.setToIdentity();
    projection.perspective(fov, (w / h), nearPlane, farPlane);
}

void ECamera::updateMovement(IEInput& input, const float dt)
{
    const float speed = this->speed * dt;

    if(input.isPressed("Forward"))
        position = position + (rotation * speed);

    if(input.isPressed("Backward"))
        position = position - (rotation * speed);

    if(input.isPressed("Left"))
        position = position - (QVector3D::crossProduct(rotation, up).normalized() * speed);

    if(input.isPressed("Right"))
        position = position + (QVector3D::crossProduct(rotation, up).normalized() * speed);

    if(input.isPressed("Up"))
        position = position + (up * speed);

    if(input.isPressed("Down"))
        position = position - (up * speed);
}

void ECamera::updateRotation(IEInput& input, const float dt)
{
    if(input.isPressed("Right Click"))
    {
        const auto& cursorPos = input.cursorPos();

        if(!isCaptured)
        {
            isCaptured = true;
            lastX = cursorPos.x();
            lastY = cursorPos.y();
        }

        float xoffset = cursorPos.x() - lastX;
        float yoffset = cursorPos.y() - lastY;

        lastX = cursorPos.x();
        lastY = cursorPos.y();

        xoffset = xoffset * (sensitivity * dt);
        yoffset = yoffset * (sensitivity * dt);

        yaw += xoffset;
        pitch -= yoffset;

        if (pitch > 89.0) { pitch = 89.0; }
        else if (pitch < -89.0) { pitch = -89.0; }

        float x = qCos(qDegreesToRadians(yaw)) * qCos(qDegreesToRadians(pitch));
        float y = qSin(qDegreesToRadians(pitch));
        float z = qSin(qDegreesToRadians(yaw)) * qCos(qDegreesToRadians(pitch));

        rotation = QVector3D(x, y, z);
    }
    else
    {
        isCaptured = false;
    }
}

void ECamera::calcModelMatrix()
{
    transform.setToIdentity();
    transform.translate(position);
    transform.rotate(0.0f, rotation.x(), rotation.y(), rotation.z());
}
