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

void EGridRenderable::setup(IEMeshManager& meshManager,
                            IEMaterialManager& materialManager,
                            IEShaderManager& shaderManager)
{
    unsigned long long meshId = IEHash::Compute("EGridMesh");
    std::unique_ptr<EGridMesh> mesh = std::make_unique<EGridMesh>(meshId);

    unsigned long long materialId = IEHash::Compute("EGridMaterial");
    std::unique_ptr<EDefaultMaterial> material = std::make_unique<EDefaultMaterial>("", materialId);
    material->setType(Type::Editor);

    unsigned long long shaderId = IEHash::Compute("EGridShader");
    std::unique_ptr<EGridShader> shader = std::make_unique<EGridShader>(shaderId);
    shader->build();

    this->setMeshId(meshId);
    this->setMaterialId(materialId);
    this->setShaderId(shaderId);
    this->addVec3Buffer("aPos", new IEVertexBuffer<QVector3D>(mesh->getPosVertices(), 12, 3, 0, 0, 0));
    this->build(*shader);

    meshManager.add(meshId, std::move(mesh));
    materialManager.add(materialId, std::move(material));
    shaderManager.add(shaderId, std::move(shader));
}
