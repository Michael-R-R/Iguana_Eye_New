#include "ECamera.h"
#include "IEInput.h"

ECamera::ECamera() :
    IECamera(),
    position(0.0f, 5.0f, 0.0f), rotation(0.0f, 0.0f, -1.0f),
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

void ECamera::updateProjection(const float w, const float h)
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
        const float x = qFloor(cursorPos.x());
        const float y = qFloor(cursorPos.y());

        if(!isCaptured)
        {
            isCaptured = true;
            lastX = x;
            lastY = y;
        }

        float xoffset = x - lastX;
        float yoffset = y - lastY;

        lastX = x;
        lastY = y;

        xoffset = xoffset * (sensitivity * dt);
        yoffset = yoffset * (sensitivity * dt);

        yaw += xoffset;
        pitch -= yoffset;

        if (pitch > 89.0) { pitch = 89.0; }
        else if (pitch < -89.0) { pitch = -89.0; }

        float rotx = qCos(qDegreesToRadians(yaw)) * qCos(qDegreesToRadians(pitch));
        float roty = qSin(qDegreesToRadians(pitch));
        float rotz = qSin(qDegreesToRadians(yaw)) * qCos(qDegreesToRadians(pitch));

        rotation = QVector3D(rotx, roty, rotz);
    }
    else
    {
        isCaptured = false;
    }
}

QDataStream& ECamera::serialize(QDataStream& out, const Serializable& obj) const
{
    IECamera::serialize(out, obj);

    const ECamera& camera = static_cast<const ECamera&>(obj);

    out << camera.position << camera.rotation
        << camera.lastX << camera.lastY << camera.yaw << camera.pitch;

    return out;
}

QDataStream& ECamera::deserialize(QDataStream& in, Serializable& obj)
{
    IECamera::deserialize(in, obj);

    ECamera& camera = static_cast<ECamera&>(obj);

    in >> camera.position >> camera.rotation
       >> camera.lastX >> camera.lastY >> camera.yaw >> camera.pitch;

    return in;
}
