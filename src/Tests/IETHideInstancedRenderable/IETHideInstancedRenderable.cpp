#include "IETHideInstancedRenderable.h"
#include "IEGame.h"
#include "IEScene.h"
#include "IEHash.h"

IETHideInstancedRenderable::IETHideInstancedRenderable()
{

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
