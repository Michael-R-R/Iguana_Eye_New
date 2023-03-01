#include "IETHideInstancedRenderable.h"
#include "IEGame.h"
#include "IEScene.h"
#include "IEHash.h"

IETHideInstancedRenderable::IETHideInstancedRenderable() :
    switchId(1), hideId(1)
{

}

void IETHideInstancedRenderable::run(IEGame* game)
{
    auto scene = game->getIEScene();
    auto ecs = scene->getECS();
    auto system = ecs->getComponent<IEECSRenderableSystem>(IEComponentType::Renderable);

    // Hide previous previous shown
    IEEntity shownEntity(hideId - 2);
    int shownIndex = system->lookUpIndex(shownEntity);
    system->addHidden(shownIndex);
    system->removeShown(shownIndex);

    // Show previous hidden
    IEEntity hiddenEntity(hideId - 1);
    int hiddenIndex = system->lookUpIndex(hiddenEntity);
    system->addShown(hiddenIndex);
    system->removeHidden(hiddenIndex);
    system->transferTempData(hiddenIndex);

    hideId++;

    // Show all 500
    if(hideId == 500)
    {
        for(int i = 0; i < 500; i++)
        {
            IEEntity hiddenEntity(i);
            int hiddenIndex = system->lookUpIndex(hiddenEntity);
            system->addShown(hiddenIndex);
            system->removeHidden(hiddenIndex);
        }
    }

    // Hide all 1000
    if(hideId == 1000)
    {
        for(int i = 0; i < 1000; i++)
        {
            IEEntity shownEntity(i);
            int shownIndex = system->lookUpIndex(shownEntity);
            system->addHidden(shownIndex);
            system->removeShown(shownIndex);
        }
    }
}

void IETHideInstancedRenderable::oneShot(IEGame* game)
{
    auto scene = game->getIEScene();
    auto ecs = scene->getECS();
    auto system = ecs->getComponent<IEECSRenderableSystem>(IEComponentType::Renderable);

    // Hide instance
    int counter = 0;
    for(int i = -10; i < 11; i++)
    {
        for(int j = -10; j < 11; j++)
        {
            IEEntity entity(++counter);
            int index = system->lookUpIndex(entity);
            if(index < 0)
                continue;

            system->addHidden(index);
            system->removeShown(index);
        }
    }

    // Show hidden
    counter = 0;
    for(int i = -10; i < 11; i+=2)
    {
        for(int j = -10; j < 11; j++)
        {
            counter += 1;
            IEEntity entity(counter);
            int index = system->lookUpIndex(entity);
            if(index < 0)
                continue;

            system->addShown(index);
            system->removeHidden(index);
            system->transferTempData(index);
        }
    }
}
