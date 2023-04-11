#pragma once

#include <QVector2D>
#include <QVector3D>
#include <QVector4D>
#include <QMatrix4x4>

class IEMath
{
public:
    static QVector3D toWorldPosition(const float w, const float h,
                                     const QVector2D& scrPos,
                                     const QVector3D& objPos,
                                     const QMatrix4x4& projection);
    static QVector3D toWorldRay(const float w, const float h,
                                const QVector2D& scrPos,
                                const QMatrix4x4& view,
                                const QMatrix4x4& projection);
};

