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
    auto mesh = QSharedPointer<IEMesh>::create(path);
    IEObjImporter::importMesh(path, *mesh);

    path = "./resources/materials/tests/mat.iemat";
    unsigned long long materialId = IEHash::Compute(path);
    auto material = QSharedPointer<IEMaterial>::create(path);
    IEUniform uniform;
    uniform.add("uColor", QColor(0, 0, 255, 255));
    material->setUniformData(uniform);

    path = "./resources/shaders/tests/instanced_renderable.glsl";
    unsigned long long shaderId = IEHash::Compute(path);
    auto shader = QSharedPointer<IEShader>::create(path);
    IEGlslImporter::importGlsl(path, *shader);
    shader->build();

    path = "./resources/renderables/tests/rend.ierend";
    unsigned long long renderableId = IEHash::Compute(path);
    auto renderable = QSharedPointer<IERenderable>::create(path,
                                                           meshId,
                                                           materialId,
                                                           shaderId);
    renderable->setDrawType(GL_TRIANGLES);
    renderable->setRenderType(IERenderable::RenderType::I_Index);

    auto indexBuffer = QSharedPointer<IEIndexBuffer>::create(mesh->getIndices());
    renderable->addIndexBuffer(indexBuffer);

    auto posBuffer = QSharedPointer<IEVertexBuffer<QVector3D>>::create(mesh->getPosVertices(), 12, 3, 0, 0, 0);
    renderable->addVec3Buffer("aPos", posBuffer);

    QMatrix4x4 transform;
    transform.translate(0.0f, 1.0f, 0.0f);
    transform.scale(1.0f, 1.0f, 1.0f);
    auto modelBuffer = QSharedPointer<IEVertexBuffer<QMatrix4x4>>::create(QVector<QMatrix4x4>{transform}, 64, 4, 64, 4, 16);
    renderable->addMat4Buffer("aModel", modelBuffer);

    renderable->addShownInstance();
    renderable->build(*shader);

    meshManager.add(meshId, mesh);
    materialManager.add(materialId, material);
    shaderManager.add(shaderId, shader);
    renderableManager.add(renderableId, renderable);
}

IETCreateRenderable::~IETCreateRenderable()
{

}
