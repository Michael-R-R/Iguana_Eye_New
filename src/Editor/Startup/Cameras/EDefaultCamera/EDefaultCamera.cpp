#include "EDefaultCamera.h"

EDefaultCamera::EDefaultCamera(const QString& path, const unsigned long long resourceId) :
    IECamera(path, resourceId)
{
    updateView(QVector3D(5.0f, 2.0f, 10.0f), QVector3D(0.0f, 0.0f, -1.0f));

    projection.perspective(fov, (800.0f / 600.0f), nearPlane, farPlane);
}
