#include "EGridMesh.h"

EGridMesh::EGridMesh(QObject* parent) :
    IEMesh(parent)
{
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

EGridMesh::~EGridMesh()
{

}
