#include "EGridRenderable.h"
#include "IEHash.h"
#include "IEMeshManager.h"
#include "IEMaterialManager.h"
#include "IEShaderManager.h"
#include "EGridMesh.h"
#include "EDefaultMaterial.h"
#include "EGridShader.h"

EGridRenderable::EGridRenderable(const unsigned long long id) :
    IERenderable("", id, 0, 0, 0)
{
    this->setType(Type::Editor);
    this->setRenderType(RenderType::Vertex);
    this->setDrawType(GL_TRIANGLES);
}

void EGridRenderable::setup(IEMeshManager* meshManager,
                            IEMaterialManager* materialManager,
                            IEShaderManager* shaderManager)
{
    unsigned long long meshId = IEHash::Compute("EGridMesh");
    auto mesh = new EGridMesh(meshId);
    meshManager->add(meshId, mesh);

    unsigned long long materialId = IEHash::Compute("EGridMaterial");
    auto material = new EDefaultMaterial("", materialId);
    material->setType(Type::Editor);
    materialManager->add(materialId, material);

    unsigned long long shaderId = IEHash::Compute("EGridShader");
    auto shader = new EGridShader(shaderId);
    shader->build();
    shaderManager->add(shaderId, shader);

    this->setMeshId(meshId);
    this->setMaterialId(materialId);
    this->setShaderId(shaderId);
    this->addVec3Buffer("aPos", new IEVertexBuffer<QVector3D>(mesh->getPosVertices(), 12, 3, 0, 0, 0));
    this->build(shader);
}
