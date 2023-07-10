#include "EGridMesh.h"

EGridMesh::EGridMesh(QObject* parent) :
    IEMesh(parent)
{
    positionVertices =
    {
        glm::vec3(1.0f, 1.0f, 0.0),
        glm::vec3(-1.0f, -1.0f, 0.0),
        glm::vec3(-1.0f, 1.0f, 0.0),
        glm::vec3(-1.0f, -1.0f, 0.0),
        glm::vec3(1.0f, 1.0f, 0.0),
        glm::vec3(1.0f, -1.0f, 0.0)
    };
}

EGridMesh::~EGridMesh()
{

}
