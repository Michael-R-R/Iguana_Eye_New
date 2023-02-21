#include "ESceneStartup.h"
#include "AppStartEvent.h"
#include "IEGame.h"
#include "IEHash.h"
#include "EGridRenderable.h"

void ESceneStartup::startup(const AppStartEvent& event)
{
    buildGridRenderable(event);
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
