#include "ECamera.h"
#include "IEinput.h"
#include "IESerializeConverter.h"
#include <glm/gtc/matrix_transform.hpp>

ECamera::ECamera(QObject* parent) :
    IECamera(parent),
    position(0.0f, 5.0f, 0.0f), rotation(0.0f, 0.0f, -1.0f),
    lastX(0.0f), lastY(0.0f), isCaptured(false),
    yaw(-90.0f), pitch(0.0f)
{

}

ECamera::~ECamera()
{

}

void ECamera::update(IEInput* input, const float dt)
{
    updateMovement(input, dt);
    updateRotation(input);
    updateView(position, rotation);
}

void ECamera::updateProjection(const float w, const float h)
{
    projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(fov), (w / h), nearPlane, farPlane);
}

void ECamera::updateMovement(IEInput* input, const float dt)
{
    const float speed = this->speed * dt;

    if(input->isPressed("Forward"))
        position += (rotation * speed);

    if(input->isPressed("Backward"))
        position -= (rotation * speed);

    if(input->isPressed("Left"))
        position -= (glm::normalize(glm::cross(rotation, up)) * speed);

    if(input->isPressed("Right"))
        position += (glm::normalize(glm::cross(rotation, up)) * speed);

    if(input->isPressed("Up"))
        position += (up * speed);

    if(input->isPressed("Down"))
        position -= (up * speed);
}

void ECamera::updateRotation(IEInput* input)
{
    if(input->isPressed("Right Click"))
    {
        const auto& cursorPos = input->cursorPos();
        const float x = cursorPos[0];
        const float y = cursorPos[1];

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

        xoffset *= sensitivity;
        yoffset *= sensitivity;

        yaw += xoffset;
        pitch -= yoffset;

        if (pitch > 89.0) { pitch = 89.0; }
        else if (pitch < -89.0) { pitch = -89.0; }

        float rotx = glm::cos(glm::radians(yaw)) * glm::cos(glm::radians(pitch));
        float roty = glm::sin(glm::radians(pitch));
        float rotz = glm::sin(glm::radians(yaw)) * glm::cos(glm::radians(pitch));

        rotation = glm::vec3(rotx, roty, rotz);
    }
    else
    {
        isCaptured = false;
    }
}

QDataStream& ECamera::serialize(QDataStream& out, const IESerializable& obj) const
{
    IECamera::serialize(out, obj);

    const ECamera& camera = static_cast<const ECamera&>(obj);

    IESerializeConverter::write(out, camera.position);
    IESerializeConverter::write(out, camera.rotation);

    out << camera.lastX
        << camera.lastY
        << camera.yaw
        << camera.pitch;

    return out;
}

QDataStream& ECamera::deserialize(QDataStream& in, IESerializable& obj)
{
    IECamera::deserialize(in, obj);

    ECamera& camera = static_cast<ECamera&>(obj);

    IESerializeConverter::read(in, camera.position);
    IESerializeConverter::read(in, camera.rotation);

    in >> camera.lastX
       >> camera.lastY
       >> camera.yaw
       >> camera.pitch;

    return in;
}
