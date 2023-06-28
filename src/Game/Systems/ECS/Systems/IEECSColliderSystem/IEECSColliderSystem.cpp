#include "IEECSColliderSystem.h"

IEECSColliderSystem::IEECSColliderSystem(QObject* parent) :
    IEECSSystem(typeid(IEECSColliderSystem).hash_code(), parent),
    data()
{
    IEECSColliderSystem::attach(IEEntity(-1));
}

IEECSColliderSystem::~IEECSColliderSystem()
{

}

int IEECSColliderSystem::attach(const IEEntity entity)
{
    if(doesExist(entity))
        return -1;

    const int index = entityMap.size();

    entityMap[entity] = index;

    data.entity.push_back(entity);
    data.collider.push_back(new IEBaseCollider(&data));

    return index;
}

bool IEECSColliderSystem::detach(const IEEntity entity)
{
    if(!doesExist(entity))
        return false;

    const int indexToRemove = entityMap[entity];

    const int lastIndex = entityMap.size() - 1;
    const IEEntity lastEntity = data.entity[lastIndex];

    this->removeCollider(indexToRemove);

    data.entity[indexToRemove] = data.entity[lastIndex];
    data.collider[indexToRemove] = data.collider[lastIndex];

    data.entity.removeLast();

    entityMap[lastEntity] = indexToRemove;
    entityMap.remove(entity);

    return true;
}

void IEECSColliderSystem::removeCollider(const int index)
{
    if(!indexBoundCheck(index))
        return;

    data.collider[index]->release();
    delete data.collider[index];
    data.collider[index] = new IEBaseCollider(&data);
}

IEBaseCollider* IEECSColliderSystem::getCollider(const int index) const
{
    if(!indexBoundCheck(index))
        return nullptr;

    return data.collider[index];
}

void IEECSColliderSystem::setCollider(const int index, IEBaseCollider* val)
{
    if(!indexBoundCheck(index))
        return;

    delete data.collider[index];
    data.collider[index] = val;
    val->setParent(&data);
}

void IEECSColliderSystem::setIsTrigger(const int index, const bool val)
{
    if(!indexBoundCheck(index))
        return;

    data.collider[index]->setIsTrigger(val);
}

QDataStream& IEECSColliderSystem::serialize(QDataStream& out, const Serializable& obj) const
{
    const IEECSColliderSystem& system = static_cast<const IEECSColliderSystem&>(obj);

    out << system.entityMap << system.data;

    return out;
}

QDataStream& IEECSColliderSystem::deserialize(QDataStream& in, Serializable& obj)
{
    IEECSColliderSystem& system = static_cast<IEECSColliderSystem&>(obj);

    in >> system.entityMap >> system.data;

    return in;
}
