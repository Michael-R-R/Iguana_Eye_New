#include "ESceneStartup.h"
#include "AppStartEvent.h"
#include "IEGame.h"
#include "IEHash.h"
#include "IESerialize.h"

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

    QString path = "./resources/meshes/editor/EGrid.iemesh";
    unsigned long long id = IEHash::Compute(path);
    nameManager->add(id, new QString(path));

    auto gridMesh = new IEMesh();
    IESerialize::read<IEMesh>(path, gridMesh);
    gridMesh->setId(id);
    meshManager->add(id, gridMesh);
}

void ESceneStartup::buildDefaultMaterials(const AppStartEvent& event)
{
    auto scene = event.getGame()->getIEScene();
    auto nameManager = scene->getNameManager();
    auto materialManager = scene->getMaterialManager();

    QString path = "./resources/materials/editor/default.iemat";
    unsigned long long id = IEHash::Compute(path);
    nameManager->add(id, new QString(path));

    auto defaultMaterial = new IEMaterial();
    IESerialize::read<IEMaterial>(path, defaultMaterial);
    defaultMaterial->setId(id);
    materialManager->add(id, defaultMaterial);
}

void ESceneStartup::buildDefaultShaders(const AppStartEvent& event)
{
    auto scene = event.getGame()->getIEScene();
    auto nameManager = scene->getNameManager();
    auto shaderManager = scene->getShaderManager();

    QString path = "./resources/shaders/editor/ERGrid.ieshader";
    unsigned long long id = IEHash::Compute(path);
    nameManager->add(id, new QString(path));

    auto gridShader = new IEShader();
    IESerialize::read<IEShader>(path, gridShader);
    gridShader->setId(id);
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

    auto gridMesh = meshManager->getValue(IEHash::Compute("./resources/meshes/editor/EGrid.iemesh"));
    auto defaultMaterial = materialManager->getValue(IEHash::Compute("./resources/materials/editor/default.iemat"));
    auto gridShader = shaderManager->getValue(IEHash::Compute("./resources/shaders/editor/ERGrid.ieshader"));

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
