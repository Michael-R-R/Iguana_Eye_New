#include "EGridMesh.h"

EGridMesh::EGridMesh(const unsigned long long id) :
    IEMesh(id)
{
    setup();
}

void EGridMesh::setup()
{
    for(int row = -10; row < 10; row++)
    {
        float rowVal = row * 0.1f;

        positionVertices.append(QVector3D(-1.0f, rowVal, 0.0f));
        positionVertices.append(QVector3D(1.0f, rowVal, 0.0f));

        for(int col = -10; col < 10; col++)
        {
            float colVal = col * 0.1f;

            positionVertices.append(QVector3D(colVal, -1.0f, 0.0f));
            positionVertices.append(QVector3D(colVal, 1.0f, 0.0f));
        }
    }
}
