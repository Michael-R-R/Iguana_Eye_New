#pragma once

#include <glm/glm.hpp>

class IEMath
{
public:
    static glm::vec3 toWorldPosition(const float w, const float h,
                                     const glm::vec2& scrPos,
                                     const glm::vec3& objPos,
                                     const glm::mat4& projection);

    static glm::vec3 toWorldRay(const float w, const float h,
                                const glm::vec2& scrPos,
                                const glm::mat4& view,
                                const glm::mat4& projection);
};

