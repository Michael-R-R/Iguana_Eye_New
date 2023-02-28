#include "IETRemoveInstancedRenderable.h"
#include "IEGame.h"
#include "IEScene.h"
#include "IEHash.h"

IETRemoveInstancedRenderable::IETRemoveInstancedRenderable() :
    row(0)
{

}

void IETRemoveInstancedRenderable::run(IEGame* game)
{
    auto scene = game->getIEScene();
    auto ecs = scene->getECS();

    int counter = 0;
    int end = row + 2;
    for(; row < end; row++)
    {
        ecs->remove(IEEntity(++counter));
    }

    row = (row > 101) ? 0 : row;
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
