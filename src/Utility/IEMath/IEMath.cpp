#include "IEMath.h"
#include <glm/gtc/matrix_transform.hpp>

glm::vec3 IEMath::toWorldPosition(const float w, const float h,
                                  const glm::vec2& scrPos,
                                  const glm::vec3& objPos,
                                  const glm::mat4& projection)
{
    // NDC
    float x = (2.0f * scrPos[0]) / w - 1.0f;
    float y = 1.0f - (2.0f * scrPos[1]) / h;
    const glm::vec2 rayNDC(x, y);

    // 4D Homogenous clip coords
    const glm::vec4 rayClip = glm::vec4(rayNDC[0], rayNDC[1], -1.0f, 1.0f);

    // World position
    glm::mat4 prjInverse = glm::inverse(projection);
    glm::vec4 rayEye = prjInverse * rayClip;
    rayEye = glm::vec4(rayEye[0], rayEye[1], -1.0f, 1.0f);

    return glm::vec3((rayEye[0] + objPos[0]),
                     (rayEye[1] + objPos[1]),
                     (rayEye[2] + objPos[2]));
}

glm::vec3 IEMath::toWorldRay(const float w, const float h,
                             const glm::vec2& scrPos,
                             const glm::mat4& view,
                             const glm::mat4& projection)
{
    // Normal device coords
    const float x = (2.0f * scrPos[0]) / w - 1.0f;
    const float y = 1.0f - (2.0f * scrPos[1]) / h;
    const float z = 1.0f;
    const glm::vec3 rayNDC = glm::vec3(x, y, z);

    // 4D homogenous clip coords
    const glm::vec4 rayClip = glm::vec4(rayNDC[0], rayNDC[1], -1.0f, 1.0f);

    // 4D world position
    glm::mat4 prjInverse = glm::inverse(projection);
    glm::vec4 rayEye = prjInverse * rayClip;
    rayEye = glm::vec4(rayEye[0], rayEye[1], -1.0f, 0.0f);

    // 4D world ray
    glm::mat4 viewInverse = glm::inverse(view);
    glm::vec4 inverseMat = viewInverse * rayEye;
    glm::vec3 rayWorld = glm::vec3(inverseMat[0], inverseMat[1], inverseMat[2]);

    return glm::normalize(rayWorld);
}
