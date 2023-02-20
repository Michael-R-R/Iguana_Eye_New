#include "ESceneStartup.h"
#include "IEHash.h"
#include "AppStartEvent.h"
#include "IEGame.h"
#include "EGridMesh.h"
#include "EDefaultMaterial.h"

void ESceneStartup::startup(const AppStartEvent& event)
{
    buildDefaultMeshes(event);
    buildDefaultMaterials(event);
    buildDefaultShaders(event);
    buildGridRenderable(event);
}

void ESceneStartup::buildDefaultMeshes(const AppStartEvent& event)
{
    auto scene = event.getGame()->getIEScene();
    auto nameManager = scene->getNameManager();
    auto meshManager = scene->getMeshManager();

    unsigned long long id = IEHash::Compute("grid_mesh");

    nameManager->add(id, new QString("grid_mesh"));
    meshManager->add(id, new EGridMesh(id));
}

void ESceneStartup::buildDefaultMaterials(const AppStartEvent& event)
{
    auto scene = event.getGame()->getIEScene();
    auto nameManager = scene->getNameManager();
    auto materialManager = scene->getMaterialManager();

    unsigned long long id = IEHash::Compute("default_material");

    nameManager->add(id, new QString("default_material"));
    materialManager->add(id, new EDefaultMaterial(id));
}

void ESceneStartup::buildDefaultShaders(const AppStartEvent& event)
{
    auto scene = event.getGame()->getIEScene();
    auto nameManager = scene->getNameManager();
    auto shaderManager = scene->getShaderManager();

    QString path = "./resources/shaders/editor/ERGrid.glsl";
    unsigned long long id = IEHash::Compute(path);

    nameManager->add(id, new QString(path));
    auto gridShader = new IEShader(id, path);
    gridShader->build();
    shaderManager->add(id, gridShader);
}

void ESceneStartup::buildGridRenderable(const AppStartEvent& event)
{
    auto scene = event.getGame()->getIEScene();
    auto nameManager = scene->getNameManager();
    auto meshManager = scene->getMeshManager();
    auto materialManager = scene->getMaterialManager();
    auto shaderManager = scene->getShaderManager();
    auto renderableManager = scene->getRenderableManager();

    auto gridMesh = meshManager->getValue(IEHash::Compute("grid_mesh"));
    auto defaultMaterial = materialManager->getValue(IEHash::Compute("default_material"));
    auto gridShader = shaderManager->getValue(IEHash::Compute("./resources/shaders/editor/ERGrid.glsl"));

    unsigned long long id = IEHash::Compute("grid_mesh+default_material+grid_shader");

    nameManager->add(id, new QString("grid_mesh+default_material+grid_shader"));
    auto gridRenderable = new IERenderable(id);
    gridRenderable->setRenderType(IERenderable::RenderType::Vertex);
    gridRenderable->setDrawType(GL_LINES);
    gridRenderable->setMeshId(gridMesh->getId());
    gridRenderable->setMaterialId(defaultMaterial->getId());
    gridRenderable->setShaderId(gridShader->getId());
    gridRenderable->addVec3Buffer("aPos", new IEVertexBuffer<QVector3D>(gridMesh->getPosVertices(), 3));
    gridRenderable->build(gridShader);
    renderableManager->add(id, gridRenderable);
}
