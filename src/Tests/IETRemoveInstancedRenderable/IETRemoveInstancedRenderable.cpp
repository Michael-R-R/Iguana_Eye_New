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
    auto scene = event.getScene();
    auto ecs = event.getScene()->getECS();
    auto renderableSystem = ecs->getComponent<IEECSRenderableSystem>(IEComponentType::Renderable);
    auto renderable = scene->getRenderableManager()->getValue(IEHash::Compute("./resources/renderables/tests/instanced_renderable.ierend"));

    for(int i = -10; i < 11; i++)
    {
        for(int j = -10; j < 11; j++)
        {

        }
    }
}
