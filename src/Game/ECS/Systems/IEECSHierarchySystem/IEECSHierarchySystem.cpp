#include "IEECSHierarchySystem.h"
#include "GameStartEvent.h"
#include "ECSOnUpdateEvent.h"

IEECSHierarchySystem::IEECSHierarchySystem() :
    IEECSSystem(),
    data()
{
    IEECSHierarchySystem::attach(IEEntity(-1));
}

IEECSHierarchySystem::~IEECSHierarchySystem()
{

}

void IEECSHierarchySystem::startup(const GameStartEvent&)
{
    // Not used
}

int IEECSHierarchySystem::attach(const IEEntity entity)
{
    if(doesExist(entity))
        return -1;

    int index = entityMap.size();

    entityMap[entity] = index;

    data.entity.append(entity);
    data.parent.append(IEEntity(-1));
    data.children.append(QVector<IEEntity>());

    return index;
}

bool IEECSHierarchySystem::detach(const IEEntity entity)
{
    if(!doesExist(entity))
        return false;

    int indexToRemove = entityMap[entity];

    // Remove from parent
    int parentIndex = this->lookUpIndex(data.parent[indexToRemove]);
    this->removeChild(parentIndex, entity);

    int lastIndex = entityMap.size() - 1;
    IEEntity lastEntity = data.entity[lastIndex];

    data.entity[indexToRemove] = data.entity[lastIndex];
    data.parent[indexToRemove] = data.parent[lastIndex];
    data.children[indexToRemove] = data.children[lastIndex];

    data.entity.removeLast();
    data.parent.removeLast();
    data.children.removeLast();

    entityMap[lastEntity] = indexToRemove;
    entityMap.remove(entity);

    return true;
}

void IEECSHierarchySystem::onUpdateFrame(ECSOnUpdateEvent*)
{
    // Not used
}

void IEECSHierarchySystem::addChild(const int parentIndex, const IEEntity childEntity)
{
    if(!indexBoundCheck(parentIndex))
        return;
    if(!doesExist(childEntity))
        return;

    const int childIndex = this->lookUpIndex(childEntity);
    data.parent[childIndex] = data.entity[parentIndex];

    data.children[parentIndex].append(childEntity);
}

void IEECSHierarchySystem::removeChild(const int parentIndex, IEEntity childEntity)
{
    if(!indexBoundCheck(parentIndex))
        return;
    if(!doesExist(childEntity))
        return;

    const int childIndex = this->lookUpIndex(childEntity);
    data.parent[childIndex] = IEEntity(-1);

    for(int i = 0; i < data.children[parentIndex].size(); i++)
    {
        if(childEntity == data.children[parentIndex][i])
        {
            data.children[parentIndex].removeAt(i);
            break;
        }
    }
}

void IEECSHierarchySystem::moveChild(const int oldParentIndex, const int newParentIndex, const IEEntity childEntity)
{
    if(!indexBoundCheck(oldParentIndex))
        return;
    if(!indexBoundCheck(newParentIndex))
        return;
    if(!doesExist(childEntity))
        return;

    removeChild(oldParentIndex, childEntity);
    addChild(newParentIndex, childEntity);
}

IEEntity IEECSHierarchySystem::getEntity(const int index) const
{
    if(!indexBoundCheck(index))
        return data.entity[0];

    return data.entity[index];
}

IEEntity IEECSHierarchySystem::getParent(const int index) const
{
    if(!indexBoundCheck(index))
        return data.parent[0];

    return data.parent[index];
}

const QVector<IEEntity>& IEECSHierarchySystem::getChildrenList(const int index) const
{
    if(!indexBoundCheck(index))
        return data.children[0];

    return data.children[index];
}
