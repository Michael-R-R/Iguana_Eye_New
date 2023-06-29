#include "IEECSTransformSystem.h"
#include "IEGame.h"
#include "IEScene.h"
#include "IEECS.h"
#include "IEECSHierarchySystem.h"
#include "IEECSRenderableSystem.h"
#include "IERenderableManager.h"
#include "IERenderable.h"

IEECSTransformSystem::IEECSTransformSystem(QObject* parent) :
    IEECSSystem(typeid(IEECSTransformSystem).hash_code(), parent),
    data(),
    dirtyParentIndices()
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
    dirtyParentIndices.insert(index);

    data.entity.append(entity);
    data.position.append(QVector3D(0.0f, 0.0f, 0.0f));
    data.rotation.append(QVector4D(0.0f, 0.0f, 0.0f, 0.0f));
    data.scale.append(QVector3D(1.0f, 1.0f, 1.0f));
    data.transform.append(QMatrix4x4());

    return index;
}

bool IEECSTransformSystem::detach(const IEEntity entity)
{
    if(!doesExist(entity))
        return false;

    int indexToRemove = entityMap[entity];

    int lastIndex = entityMap.size() - 1;
    IEEntity lastEntity = data.entity[lastIndex];

    data.entity[indexToRemove] = data.entity[lastIndex];
    data.position[indexToRemove] = data.position[lastIndex];
    data.rotation[indexToRemove] = data.rotation[lastIndex];
    data.scale[indexToRemove] = data.scale[lastIndex];
    data.transform[indexToRemove] = data.transform[lastIndex];

    data.entity.removeLast();
    data.position.removeLast();
    data.rotation.removeLast();
    data.scale.removeLast();
    data.transform.removeLast();

    entityMap[lastEntity] = indexToRemove;
    entityMap.remove(entity);

    dirtyParentIndices.remove(indexToRemove);

    return true;
}

void IEECSTransformSystem::startUp(const IEGame& game)
{
    auto* ecs = game.getSystem<IEECS>();
    hSystem = ecs->getComponent<IEECSHierarchySystem>();
    rSystem = ecs->getComponent<IEECSRenderableSystem>();
    renderableManager = game.getSystem<IEScene>()->getManager<IERenderableManager>();
}

void IEECSTransformSystem::shutdown(const IEGame&)
{
    hSystem = nullptr;
    rSystem = nullptr;
    renderableManager = nullptr;
}

void IEECSTransformSystem::onUpdateFrame()
{
    for(const auto& i : qAsConst(dirtyParentIndices))
    {
        QSet<int> dirtyChildIndices;
        updateTransform(i, dirtyChildIndices);

        for(const auto& j : qAsConst(dirtyChildIndices))
        {
            const IEEntity& childEntity = data.entity[j];
            const int childIndex = rSystem->lookUpIndex(childEntity);
            const uint64_t renderableId = rSystem->getResourceId(childIndex);
            auto renderable = renderableManager->value<IERenderable>(renderableId);
            if(!renderable)
                continue;

            QMatrix4x4& transform = data.transform[j];
            const int childInstanceIndex = rSystem->getShownInstanceIndex(childIndex);
            renderable->setMat4InstanceValue("aModel", childInstanceIndex, transform);
        }

        const IEEntity& parentEntity = data.entity[i];
        const int parentIndex = rSystem->lookUpIndex(parentEntity);
        const uint64_t renderableId = rSystem->getResourceId(parentIndex);
        auto renderable = renderableManager->value<IERenderable>(renderableId);
        if(!renderable)
            continue;

        QMatrix4x4& transform = data.transform[i];
        const int parentInstanceIndex = rSystem->getShownInstanceIndex(parentIndex);
        renderable->setMat4InstanceValue("aModel", parentInstanceIndex, transform);
    }

    dirtyParentIndices.clear();
}

const QVector3D& IEECSTransformSystem::getPosition(const int index) const
{
    if(!indexBoundCheck(index))
        return data.position[0];

    return data.position[index];
}

const QVector4D& IEECSTransformSystem::getRotation(const int index) const
{
    if(!indexBoundCheck(index))
        return data.rotation[0];

    return data.rotation[index];
}

const QVector3D& IEECSTransformSystem::getScale(const int index) const
{
    if(!indexBoundCheck(index))
        return data.scale[0];

    return data.scale[index];
}

const QMatrix4x4& IEECSTransformSystem::getTransform(const int index) const
{
    if(!indexBoundCheck(index))
        return data.transform[0];

    return data.transform[index];
}

void IEECSTransformSystem::setPosition(const int index, const QVector3D& val)
{
    if(!indexBoundCheck(index))
        return;

    data.position[index] = val;

    dirtyParentIndices.insert(index);
}

void IEECSTransformSystem::setRotation(const int index, const QVector3D& val)
{
    if(!indexBoundCheck(index))
        return;

    data.rotation[index] = QVector4D(val.x(), val.y(), val.z(), 0.0f);

    dirtyParentIndices.insert(index);
}

void IEECSTransformSystem::setRotation(const int index, const QVector4D& val)
{
    if(!indexBoundCheck(index))
        return;

    data.rotation[index] = val;

    dirtyParentIndices.insert(index);
}

void IEECSTransformSystem::setScale(const int index, const QVector3D& val)
{
    if(!indexBoundCheck(index))
        return;

    data.scale[index] = val;

    dirtyParentIndices.insert(index);
}

void IEECSTransformSystem::updateTransform(const int index,
                                           QSet<int>& dirtyChildren)
{
    if(!indexBoundCheck(index))
        return;

    IEEntity entity = data.entity[index];

    int hierarchyIndex = hSystem->lookUpIndex(entity);
    IEEntity parentEntity = hSystem->getParent(hierarchyIndex);
    int parentTransformIndex = this->lookUpIndex(parentEntity);

    if(parentTransformIndex > 0)
    {
        // Update child relative to parent
        data.transform[index] = data.transform[parentTransformIndex] * calcModelMatrix(index);
        dirtyChildren.insert(index);
    }
    else
    {
        // Update parent
        data.transform[index] = calcModelMatrix(index);
    }

    for(auto& childEntity : hSystem->getChildrenList(hierarchyIndex))
    {
        int childIndex = this->lookUpIndex(childEntity);
        this->updateTransform(childIndex, dirtyChildren);
    }
}

QMatrix4x4 IEECSTransformSystem::calcModelMatrix(const int index)
{
    if(!indexBoundCheck(index))
        return QMatrix4x4();

    auto& pos = data.position[index];
    auto& rot = data.rotation[index];
    auto& scl = data.scale[index];

    QMatrix4x4 transform;
    transform.translate(pos);
    transform.rotate(rot.w(), rot.x(), rot.y(), rot.z());
    transform.scale(scl);

    return transform;
}

QDataStream& IEECSTransformSystem::serialize(QDataStream& out, const Serializable& obj) const
{
    const auto& system = static_cast<const IEECSTransformSystem&>(obj);

    out << system.entityMap << system.data;

    return out;
}

QDataStream& IEECSTransformSystem::deserialize(QDataStream& in, Serializable& obj)
{
    auto& system = static_cast<IEECSTransformSystem&>(obj);

    in >> system.entityMap >> system.data;

    return in;
}
