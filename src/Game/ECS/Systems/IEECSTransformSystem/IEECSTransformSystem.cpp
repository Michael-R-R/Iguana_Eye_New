#include "IEECSTransformSystem.h"
#include "ECSOnUpdateEvent.h"
#include "IEECSHierarchySystem.h"

IEECSTransformSystem::IEECSTransformSystem() :
    IEECSSystem(),
    data(),
    dirtyParents()
{
    IEECSTransformSystem::attach(IEEntity(-1));
}

IEECSTransformSystem::~IEECSTransformSystem()
{

}

int IEECSTransformSystem::attach(const IEEntity entity)
{
    if(doesExist(entity))
        return -1;

    int index = entityMap.size();

    entityMap[entity] = index;
    dirtyParents[entity] = index;

    data.entityList.append(entity);
    data.positionList.append(QVector3D(0.0f, 0.0f, 0.0f));
    data.rotationList.append(QVector3D(0.0f, 0.0f, 0.0f));
    data.scaleList.append(QVector3D(1.0f, 1.0f, 1.0f));
    data.transformList.append(QMatrix4x4());

    return index;
}

bool IEECSTransformSystem::detach(const IEEntity entity)
{
    if(!doesExist(entity))
        return false;

    int indexToRemove = entityMap[entity];

    int lastIndex = entityMap.size() - 1;
    IEEntity lastEntity = data.entityList[lastIndex];

    data.entityList[indexToRemove] = data.entityList[lastIndex];
    data.positionList[indexToRemove] = data.positionList[lastIndex];
    data.rotationList[indexToRemove] = data.rotationList[lastIndex];
    data.scaleList[indexToRemove] = data.scaleList[lastIndex];
    data.transformList[indexToRemove] = data.transformList[lastIndex];

    data.entityList.removeLast();
    data.positionList.removeLast();
    data.rotationList.removeLast();
    data.scaleList.removeLast();
    data.transformList.removeLast();

    entityMap[lastEntity] = indexToRemove;
    entityMap.remove(entity);

    dirtyParents.remove(entity);

    return true;
}

void IEECSTransformSystem::onUpdateFrame(ECSOnUpdateEvent* event)
{
    QMapIterator<IEEntity, int> itParent(dirtyParents);
    while(itParent.hasNext())
    {
        itParent.next();

        QMap<IEEntity, int> dirtyChildren;
        updateTransform(itParent.value(), dirtyChildren, event->getHierarchy());

        QMapIterator<IEEntity, int> itChild(dirtyChildren);
        while(itChild.hasNext())
        {
            itChild.next();

            // TODO update child renderable instance
        }

        // TODO update parent renderable instance
    }

    dirtyParents.clear();
}

const QVector3D& IEECSTransformSystem::getPosition(const int index) const
{
    if(!indexBoundCheck(index))
        return data.positionList[0];

    return data.positionList[index];
}

const QVector3D& IEECSTransformSystem::getRotation(const int index) const
{
    if(!indexBoundCheck(index))
        return data.rotationList[0];

    return data.rotationList[index];
}

const QVector3D& IEECSTransformSystem::getScale(const int index) const
{
    if(!indexBoundCheck(index))
        return data.scaleList[0];

    return data.scaleList[index];
}

const QMatrix4x4& IEECSTransformSystem::getTransform(const int index) const
{
    if(!indexBoundCheck(index))
        return data.transformList[0];

    return data.transformList[index];
}

void IEECSTransformSystem::setPosition(const int index, const QVector3D& val)
{
    if(!indexBoundCheck(index))
        return;

    data.positionList[index] = val;

    dirtyParents[data.entityList[index]] = index;
}

void IEECSTransformSystem::setRotation(const int index, const QVector3D& val)
{
    if(!indexBoundCheck(index))
        return;

    data.rotationList[index] = val;

    dirtyParents[data.entityList[index]] = index;
}

void IEECSTransformSystem::setScale(const int index, const QVector3D& val)
{
    if(!indexBoundCheck(index))
        return;

    data.scaleList[index] = val;

    dirtyParents[data.entityList[index]] = index;
}

void IEECSTransformSystem::setTransform(const int index, const QMatrix4x4& val)
{
    if(!indexBoundCheck(index))
        return;

    data.transformList[index] = val;

    dirtyParents[data.entityList[index]] = index;
}

void IEECSTransformSystem::updateTransform(const int index,
                                           QMap<IEEntity, int>& dirtyChildren,
                                           const IEECSHierarchySystem* hierarchySystem)
{
    if(!indexBoundCheck(index))
        return;

    IEEntity entity = data.entityList[index];

    int hierarchyIndex = hierarchySystem->lookUpIndex(entity);
    IEEntity parentEntity = hierarchySystem->getParent(hierarchyIndex);

    int parentTransformIndex = this->lookUpIndex(parentEntity);
    if(parentTransformIndex > 0)
    {
        // Update child entity
        data.transformList[index] = data.transformList[parentTransformIndex] * calcModelMatrix(index);
        dirtyChildren[entity] = index;
    }
    else
    {
        // Update parent entity
        data.transformList[index] = calcModelMatrix(index);
    }

    for(auto& childEntity : hierarchySystem->getChildrenList(hierarchyIndex))
    {
        int childIndex = this->lookUpIndex(childEntity);
        this->updateTransform(childIndex, dirtyChildren, hierarchySystem);
    }
}

QMatrix4x4 IEECSTransformSystem::calcModelMatrix(const int index)
{
    if(!indexBoundCheck(index))
        return QMatrix4x4();

    auto& pos = data.positionList[index];
    auto& rot = data.rotationList[index];
    auto& scl = data.scaleList[index];

    QMatrix4x4 transform;
    transform.translate(pos);
    transform.rotate(rot.x(), 1.0f, 0.0f, 0.0f);
    transform.rotate(rot.y(), 0.0f, 1.0f, 0.0f);
    transform.rotate(rot.z(), 0.0f, 0.0f, 1.0f);
    transform.scale(scl);

    return transform;
}
