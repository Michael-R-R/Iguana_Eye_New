#include "EGridMesh.h"

EGridMesh::EGridMesh(QObject* parent) :
    IEMesh(parent)
{
    auto* node = new IEMeshNode();

    node->positions =
    {
        glm::vec3(1.0f, 1.0f, 0.0),
        glm::vec3(-1.0f, -1.0f, 0.0),
        glm::vec3(-1.0f, 1.0f, 0.0),
        glm::vec3(-1.0f, -1.0f, 0.0),
        glm::vec3(1.0f, 1.0f, 0.0),
        glm::vec3(1.0f, -1.0f, 0.0)
    };

    IEMesh::appendNode(node);
}

EGridMesh::~EGridMesh()
{

}
