#include "IETRemoveInstancedRenderable.h"
#include "IEGame.h"
#include "IEScene.h"
#include "IEHash.h"

IETRemoveInstancedRenderable::IETRemoveInstancedRenderable() :
    row(-11), col(-11), switchId(1)
{

}

void IETRemoveInstancedRenderable::run(IEGame* game)
{
    switchId = (switchId == 1) ? 2 : 1;
    qDebug() << "Switch id:" << switchId;
    auto scene = game->getIEScene();
    auto ecs = scene->getECS();

    ecs->remove(IEEntity(switchId));
}

void IETRemoveInstancedRenderable::oneShot(IEGame* game)
{
    auto scene = game->getIEScene();
    auto ecs = scene->getECS();

    int counter = 0;
    for(int i = -10; i < 11; i++)
    {
        for(int j = -10; j < 11; j++)
        {
            ecs->remove(IEEntity(++counter));
        }
    }
}
