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

    int counter = 0;
    for(int i = 0; i < 11; i++)
    {
        for(int j = 0; j < 20; j++)
        {
            IEEntity entity;
            int instanceIndex;
            std::tie(entity, instanceIndex) = renderable->removeInstance(IEEntity(++counter));
            renderable->purgeInstanceValues(instanceIndex);

            int index = renderableSystem->lookUpIndex(entity);
            renderableSystem->setRenderableId(index, 0);
            renderableSystem->setInstanceIndex(index, -1);
        }
    }
}
