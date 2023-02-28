#include "IETRemoveInstancedRenderable.h"
#include "GameStartEvent.h"
#include "IEScene.h"
#include "IEHash.h"

IETRemoveInstancedRenderable::IETRemoveInstancedRenderable(const GameStartEvent& event)
{
    setup(event);
}

void IETRemoveInstancedRenderable::setup(const GameStartEvent& event)
{
    auto ecs = event.getScene()->getECS();

    int counter = 0;
    for(int i = 0; i < 11; i++)
    {
        for(int j = 0; j < 20; j++)
        {
            ecs->remove(IEEntity(++counter));
        }
    }
}
