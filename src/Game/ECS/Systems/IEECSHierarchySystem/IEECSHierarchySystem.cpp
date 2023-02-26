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

    data.entityList.append(entity);
    data.parentList.append(IEEntity(-1));
    data.childrenList.append(QVector<IEEntity>());

    return index;
}

bool IEECSHierarchySystem::detach(const IEEntity entity)
{
    if(!doesExist(entity))
        return false;

    int indexToRemove = entityMap[entity];

    // Remove from parent
    int parentIndex = this->lookUpIndex(data.parentList[indexToRemove]);
    this->removeChild(parentIndex, entity);

    int lastIndex = entityMap.size() - 1;
    IEEntity lastEntity = data.entityList[lastIndex];

    data.entityList[indexToRemove] = data.entityList[lastIndex];
    data.parentList[indexToRemove] = data.parentList[lastIndex];
    data.childrenList[indexToRemove] = data.childrenList[lastIndex];

    data.entityList.removeLast();
    data.parentList.removeLast();
    data.childrenList.removeLast();

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
    data.parentList[childIndex] = data.entityList[parentIndex];

    data.childrenList[parentIndex].append(childEntity);
}

void IEECSHierarchySystem::removeChild(const int parentIndex, IEEntity childEntity)
{
    if(!indexBoundCheck(parentIndex))
        return;
    if(!doesExist(childEntity))
        return;

    const int childIndex = this->lookUpIndex(childEntity);
    data.parentList[childIndex] = IEEntity(-1);

    for(int i = 0; i < data.childrenList[parentIndex].size(); i++)
    {
        if(childEntity == data.childrenList[parentIndex][i])
        {
            data.childrenList[parentIndex].removeAt(i);
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
        return data.entityList[0];

    return data.entityList[index];
}

IEEntity IEECSHierarchySystem::getParent(const int index) const
{
    if(!indexBoundCheck(index))
        return data.parentList[0];

    return data.parentList[index];
}

const QVector<IEEntity>& IEECSHierarchySystem::getChildrenList(const int index) const
{
    if(!indexBoundCheck(index))
        return data.childrenList[0];

    return data.childrenList[index];
}
