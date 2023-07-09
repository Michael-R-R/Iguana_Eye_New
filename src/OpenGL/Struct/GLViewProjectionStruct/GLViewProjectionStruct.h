#pragma once

#include <glm/glm.hpp>

struct GLViewProjectionStruct
{
    glm::mat4 view;
    glm::mat4 projection;
    glm::mat4 viewProjection;

    GLViewProjectionStruct() :
        view(),
        projection(),
        viewProjection()
    {

    }

    GLViewProjectionStruct(const glm::mat4& view, const glm::mat4& projection) :
        view(view),
        projection(projection),
        viewProjection(projection * view)
    {

    }
};

