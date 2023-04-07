#include "IETCreateRenderable.h"
#include "IEGame.h"
#include "IEScene.h"
#include "IEMeshManager.h"
#include "IEMaterialManager.h"
#include "IEShaderManager.h"
#include "IERenderableManager.h"
#include "IEMesh.h"
#include "IEMaterial.h"
#include "IEShader.h"
#include "IERenderable.h"
#include "IEIndexBuffer.h"
#include "IEVertexBuffer.h"
#include "IEObjImporter.h"
#include "IEGlslImporter.h"
#include "IEHash.h"

IETCreateRenderable::IETCreateRenderable()
{
    auto& scene = IEScene::instance();
    auto& meshManager = scene.getMeshManager();
    auto& materialManager = scene.getMaterialManager();
    auto& shaderManager = scene.getShaderManager();
    auto& renderableManager = scene.getRenderableManager();

    QString path = "./resources/meshes/tests/cube.obj";
    unsigned long long meshId = IEHash::Compute(path);
    auto mesh = std::make_unique<IEMesh>(path, meshId);
    mesh->setType(IEResource::Type::Game);
    IEObjImporter::importMesh(path, *mesh);

    path = "./resources/materials/tests/mat.iemat";
    unsigned long long materialId = IEHash::Compute(path);
    auto material = std::make_unique<IEMaterial>(path, materialId);
    material->setType(IEResource::Type::Game);
    IEUniform uniform;
    uniform.add("uColor", QColor(0, 0, 255, 255));
    material->setUniformData(uniform);

    path = "./resources/shaders/tests/instanced_renderable.glsl";
    unsigned long long shaderId = IEHash::Compute(path);
    auto shader = std::make_unique<IEShader>(path, shaderId);
    shader->setType(IEResource::Type::Game);
    IEGlslImporter::importGlsl(path, *shader);
    shader->build();

    path = "./resources/renderables/tests/rend.ierend";
    unsigned long long renderableId = IEHash::Compute(path);
    auto renderable = std::make_unique<IERenderable>(path, renderableId,
                                                     meshId,
                                                     materialId,
                                                     shaderId);
    renderable->setType(IEResource::Type::Game);
    renderable->setDrawType(GL_TRIANGLES);
    renderable->setRenderType(IERenderable::RenderType::I_Index);

    auto indexBuffer = std::make_unique<IEIndexBuffer>(mesh->getIndices());
    renderable->addIndexBuffer(std::move(indexBuffer));

    auto posBuffer = std::make_unique<IEVertexBuffer<QVector3D>>(mesh->getPosVertices(), 12, 3, 0, 0, 0);
    renderable->addVec3Buffer("aPos", std::move(posBuffer));

    QMatrix4x4 transform;
    transform.translate(0.0f, 1.0f, 0.0f);
    transform.scale(1.0f, 1.0f, 1.0f);
    auto modelBuffer = std::make_unique<IEVertexBuffer<QMatrix4x4>>(QVector<QMatrix4x4>{transform}, 64, 4, 64, 4, 16);
    renderable->addMat4Buffer("aModel", std::move(modelBuffer));

    renderable->addShownInstance();
    renderable->build(*shader);

    meshManager.add(meshId, std::move(mesh));
    materialManager.add(materialId, std::move(material));
    shaderManager.add(shaderId, std::move(shader));
    renderableManager.add(renderableId, std::move(renderable));
}

IETCreateRenderable::~IETCreateRenderable()
{

}
