#include "IETCreateRenderable.h"
#include "ApplicationWindow.h"
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
    auto* game = ApplicationWindow::instance().getGame();
    auto& scene = game->getScene();
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
    QSharedPointer<IERenderable> renderable = QSharedPointer<IERenderable>::create(path,
                                                           meshId,
                                                           materialId,
                                                           shaderId);
    renderable->setDrawType(GL_TRIANGLES);
    renderable->setRenderMode(IERenderable::RenderMode::I_Index);

    auto indexBuffer = QSharedPointer<IEIndexBuffer>::create(mesh->getIndices());
    renderable->addIndexBuffer(indexBuffer);

    auto posBuffer = QSharedPointer<IEVertexBuffer<QVector3D>>::create(mesh->getPosVertices(), 12, 3, 0, 0, 0);
    renderable->addVec3Buffer("aPos", posBuffer);

    auto modelBuffer = QSharedPointer<IEVertexBuffer<QMatrix4x4>>::create(QVector<QMatrix4x4>(), 68, 4, 68, 4, 16);
    renderable->addMat4Buffer("aModel", modelBuffer);
    renderable->build(*shader);

    renderable->addShownInstance();
    renderable->addShownInstance();
    renderable->addShownInstance();

    QMatrix4x4 t1;
    t1.translate(QVector3D(0.0f, 0.0f, 0.0f));
    t1.scale(QVector3D(1.0f, 1.0f, 1.0f));
    renderable->setMat4InstanceValue("aModel", 0, t1);
    QMatrix4x4 t2;
    t2.translate(QVector3D(0.0f, 10.0f, 0.0f));
    t2.scale(QVector3D(1.0f, 1.0f, 1.0f));
    renderable->setMat4InstanceValue("aModel", 1, t2);
    QMatrix4x4 t3;
    t3.translate(QVector3D(5.0f, 0.0f, 0.0f));
    t3.scale(QVector3D(1.0f, 1.0f, 1.0f));
    renderable->setMat4InstanceValue("aModel", 2, t3);

    meshManager.add(meshId, mesh);
    materialManager.add(materialId, material);
    shaderManager.add(shaderId, shader);
    renderableManager.add(renderableId, renderable);
}

IETCreateRenderable::~IETCreateRenderable()
{

}
