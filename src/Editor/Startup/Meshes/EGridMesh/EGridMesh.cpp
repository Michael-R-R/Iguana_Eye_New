#include "EGridMesh.h"

EGridMesh::EGridMesh(const unsigned long long id) :
    IEMesh("", id)
{
    this->setType(Type::Editor);

    positionVertices =
    {
        QVector3D(1.0f, 1.0f, 0.0),
        QVector3D(-1.0f, -1.0f, 0.0),
        QVector3D(-1.0f, 1.0f, 0.0),
        QVector3D(-1.0f, -1.0f, 0.0),
        QVector3D(1.0f, 1.0f, 0.0),
        QVector3D(1.0f, -1.0f, 0.0)
    };
}
