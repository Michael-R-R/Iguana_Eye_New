#pragma once

#include <glm/glm.hpp>

struct GLSCamera
{
    glm::vec4 position;
    glm::vec4 rotation;

    GLSCamera() :
        position(), rotation()
    {

    }

    GLSCamera(const glm::vec4& p, const glm::vec4& r) :
        position(p), rotation(r)
    {

    }
};
