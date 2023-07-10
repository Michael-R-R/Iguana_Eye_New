#pragma once

#include <glm/glm.hpp>

struct GLSViewProjection
{
    glm::mat4 view;
    glm::mat4 projection;
    glm::mat4 viewProjection;

    GLSViewProjection() :
        view(),
        projection(),
        viewProjection()
    {

    }

    GLSViewProjection(const glm::mat4& view, const glm::mat4& projection) :
        view(view),
        projection(projection),
        viewProjection(projection * view)
    {

    }
};

