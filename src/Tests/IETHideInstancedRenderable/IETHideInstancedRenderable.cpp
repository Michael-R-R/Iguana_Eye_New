#include "IETHideInstancedRenderable.h"
#include "GameStartEvent.h"
#include "IEScene.h"
#include "IEHash.h"

IETHideInstancedRenderable::IETHideInstancedRenderable(const GameStartEvent& event)
{
    setup(event);
}

void IETHideInstancedRenderable::setup(const GameStartEvent& event)
{
    auto ecs = event.getScene()->getECS();
    auto manager = event.getScene()->getRenderableManager();
    auto system = ecs->getComponent<IEECSRenderableSystem>(IEComponentType::Renderable);

    // Hide instance
    int counter = 0;
    for(int i = -10; i < 11; i++)
    {
        for(int j = -10; j < 20; j++)
        {
            IEEntity entity(++counter);
            int entityIndex = system->lookUpIndex(entity);
            if(entityIndex < 0)
                continue;

            const auto id = system->getRenderableId(entityIndex);
            const auto instanceIndex = system->getShownInstanceIndex(entityIndex);
            auto renderable = manager->getValue(id);

            QMap<QString, QVector2D> vec2Data;
            renderable->fetchBufferDataAtIndex(instanceIndex, vec2Data);

            IEEntity movedEntity;
            int indexAt = -1;
            std::tie(movedEntity, indexAt) = renderable->removeShownInstance(entity);
            if(indexAt > -1)
            {
                int movedEntityIndex = system->lookUpIndex(movedEntity);
                system->setShownInstanceIndex(movedEntityIndex, indexAt);
            }

            system->setShownInstanceIndex(entityIndex, -1);
            system->setTempVec2Data(entityIndex, vec2Data);

            int hiddenIndex = renderable->addHiddenInstance(entity);
            system->setHiddenInstanceIndex(entityIndex, hiddenIndex);
        }
    }

    // Show hidden
    counter = 0;
    for(int i = -10; i < 11; i++)
    {
        for(int j = -10; j < 11; j++)
        {
            counter += 1;
            IEEntity entity(counter);
            int entityIndex = system->lookUpIndex(entity);
            if(entityIndex < 0)
                continue;

            const auto id = system->getRenderableId(entityIndex);
            auto renderable = manager->getValue(id);

            IEEntity movedEntity;
            int indexAt = -1;
            std::tie(movedEntity, indexAt) = renderable->removeHiddenInstance(entity);
            if(indexAt > -1)
            {
                int movedEntityIndex = system->lookUpIndex(movedEntity);
                system->setHiddenInstanceIndex(movedEntityIndex, indexAt);
            }

            auto tempVec2Data = system->getTempVec2Data(entityIndex);
            system->setTempVec2Data(entityIndex, QMap<QString, QVector2D>());

            QMapIterator<QString, QVector2D> it(tempVec2Data);
            while(it.hasNext())
            {
                it.next();
                int instanceIndex = renderable->addShownInstance(entity);
                renderable->appendVec2InstanceValue(it.key(), it.value());
                system->setShownInstanceIndex(entityIndex, instanceIndex);
            }
        }
    }
}
