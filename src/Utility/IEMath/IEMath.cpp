#include "IEMath.h"

QVector3D IEMath::toWorldPosition(const float w, const float h,
                                  const QVector2D& scrPos,
                                  const QVector3D& objPos,
                                  const QMatrix4x4& projection)
{
    // NDC
    float x = (2.0f * scrPos.x()) / w - 1.0f;
    float y = 1.0f - (2.0f * scrPos.y()) / h;
    const QVector2D rayNDC(x, y);

    // 4D Homogenous clip coords
    const QVector4D rayClip = QVector4D(rayNDC.x(), rayNDC.y(), -1.0f, 1.0f);

    // World position
    QVector4D rayEye = projection.inverted() * rayClip;
    rayEye = QVector4D(rayEye.x(), rayEye.y(), -1.0f, 1.0f);

    return QVector3D((rayEye.x() + objPos.x()),
                     (rayEye.y() + objPos.y()),
                     (rayEye.z() + objPos.z()));
}

QVector3D IEMath::toWorldRay(const float w, const float h,
                             const QVector2D& scrPos,
                             const QMatrix4x4& view,
                             const QMatrix4x4& projection)
{
    // Normal device coords
    const float x = (2.0f * scrPos.x()) / w - 1.0f;
    const float y = 1.0f - (2.0f * scrPos.y()) / h;
    const float z = 1.0f;
    const QVector3D rayNDC = QVector3D(x, y, z);

    // 4D homogenous clip coords
    const QVector4D rayClip = QVector4D(rayNDC.x(), rayNDC.y(), -1.0f, 1.0f);

    // 4D world position
    QVector4D rayEye = projection.inverted() * rayClip;
    rayEye = QVector4D(rayEye.x(), rayEye.y(), -1.0f, 0.0f);

    // 4D world ray
    QVector4D inverseMat = view.inverted() * rayEye;
    QVector3D rayWorld = QVector3D(inverseMat.x(), inverseMat.y(), inverseMat.z());

    return rayWorld.normalized();
}
