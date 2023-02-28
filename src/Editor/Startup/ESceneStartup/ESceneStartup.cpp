#include "ESceneStartup.h"
#include "AppStartEvent.h"
#include "IEGame.h"
#include "IEHash.h"
#include "IESerialize.h"
#include "EGridRenderable.h"

void ESceneStartup::startup(const AppStartEvent& event)
{
    addDefaultMaterial(event);
    addDefaultShader(event);
    buildGridRenderable(event);
}

void ESceneStartup::addDefaultMaterial(const AppStartEvent& event)
{
    auto scene = event.getGame()->getIEScene();

    QString path = "./resources/materials/game/default.iemat";
    unsigned long long id = IEHash::Compute(path);
    auto material = new IEMaterial(path, id);
    material->setType(IEResource::Type::Editor);
    if(!IESerialize::read<IEMaterial>(path, material))
        IESerialize::write<IEMaterial>(path, material);
    scene->getMaterialManager()->add(id, material);
}

void ESceneStartup::addDefaultShader(const AppStartEvent& event)
{
    auto scene = event.getGame()->getIEScene();

    QString path = "./resources/shaders/game/default.glsl";
    unsigned long long id = IEHash::Compute(path);
    auto shader = new IEShader(path, id);
    shader->setType(IEResource::Type::Editor);
    IEGlslImporter::importGlsl(path, shader);
    shader->build();
    scene->getShaderManager()->add(id, shader);
}

void ESceneStartup::buildGridRenderable(const AppStartEvent& event)
{
    auto scene = event.getGame()->getIEScene();
    auto meshManager = scene->getMeshManager();
    auto materialManager = scene->getMaterialManager();
    auto shaderManager = scene->getShaderManager();
    auto renderableManager = scene->getRenderableManager();

    unsigned long long id = IEHash::Compute("EGridRenderable");
    auto gridRenderable = new EGridRenderable(id);
    gridRenderable->setup(meshManager, materialManager, shaderManager);
    renderableManager->add(id, gridRenderable);
}
