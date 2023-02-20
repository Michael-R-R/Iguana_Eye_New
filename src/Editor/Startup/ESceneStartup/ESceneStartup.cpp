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

    QString path = "./resources/meshes/editor/EGridMesh.iemesh";
    unsigned long long id = IEHash::Compute(path);
    nameManager->add(id, new QString(path));

    auto gridMesh = new IEMesh();
    IESerialize::read<IEMesh>(path, gridMesh);
    gridMesh->setFilePath(path);
    gridMesh->setId(id);
    meshManager->add(id, gridMesh);
}

void ESceneStartup::buildDefaultMaterials(const AppStartEvent& event)
{
    auto scene = event.getGame()->getIEScene();
    auto nameManager = scene->getNameManager();
    auto materialManager = scene->getMaterialManager();

    QString path = "./resources/materials/editor/EDefaultMaterial.iemat";
    unsigned long long id = IEHash::Compute(path);
    nameManager->add(id, new QString(path));

    auto defaultMaterial = new IEMaterial();
    IESerialize::read<IEMaterial>(path, defaultMaterial);
    defaultMaterial->setFilePath(path);
    defaultMaterial->setId(id);
    materialManager->add(id, defaultMaterial);
}

void ESceneStartup::buildDefaultShaders(const AppStartEvent& event)
{
    auto scene = event.getGame()->getIEScene();
    auto nameManager = scene->getNameManager();
    auto shaderManager = scene->getShaderManager();

    QString path = "./resources/shaders/editor/EGridShader.ieshader";
    unsigned long long id = IEHash::Compute(path);
    nameManager->add(id, new QString(path));

    auto gridShader = new IEShader();
    IESerialize::read<IEShader>(path, gridShader);
    gridShader->setFilePath(path);
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

    auto mesh = meshManager->getValue(IEHash::Compute("./resources/meshes/editor/EGridMesh.iemesh"));
    auto material = materialManager->getValue(IEHash::Compute("./resources/materials/editor/EDefaultMaterial.iemat"));
    auto gridShader = shaderManager->getValue(IEHash::Compute("./resources/shaders/editor/EGridShader.ieshader"));

    QString path = "./resources/renderables/editor/EGridRenderable.ierend";
    unsigned long long id = IEHash::Compute(path);
    nameManager->add(id, new QString(path));

    auto gridRenderable = new IERenderable();
    IESerialize::read<IERenderable>(path, gridRenderable);
    gridRenderable->setFilePath(path);
    gridRenderable->setId(id);
    gridRenderable->setMeshId(mesh->getId());
    gridRenderable->setMaterialId(material->getId());
    gridRenderable->setShaderId(gridShader->getId());
    gridRenderable->build(gridShader);
    renderableManager->add(id, gridRenderable);
}
