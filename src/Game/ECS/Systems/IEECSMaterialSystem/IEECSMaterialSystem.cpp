#include "IEECSMaterialSystem.h"
#include "GameStartEvent.h"
#include "ECSOnUpdateEvent.h"
#include "IEScene.h"
#include "IEMaterialManager.h"

IEECSMaterialSystem::IEECSMaterialSystem() :
    IEECSSystem(),
    data(),
    materialManager(nullptr)
{
    IEECSMaterialSystem::attach(IEEntity(-1));
}

IEECSMaterialSystem::~IEECSMaterialSystem()
{
    materialManager = nullptr;
}

void IEECSMaterialSystem::startup(const GameStartEvent& event)
{
    materialManager = &event.getScene().getMaterialManager();
}

int IEECSMaterialSystem::attach(const IEEntity entity)
{
    if(doesExist(entity))
        return -1;

    int index = entityMap.size();

    entityMap[entity] = index;

    data.entity.append(entity);
    data.materialId.append(0);

    return index;
}

bool IEECSMaterialSystem::detach(const IEEntity entity)
{
    if(!doesExist(entity))
        return false;

    const int indexToRemove = entityMap[entity];

    const int lastIndex = entityMap.size() - 1;
    const IEEntity lastEntity = data.entity[lastIndex];

    data.entity[indexToRemove] = data.entity[lastIndex];
    data.materialId[indexToRemove] = data.materialId[lastIndex];

    data.entity.removeLast();
    data.materialId.removeLast();

    entityMap[lastEntity] = indexToRemove;
    entityMap.remove(entity);

    return true;
}

void IEECSMaterialSystem::onUpdateFrame(ECSOnUpdateEvent*)
{
    // Not used
}

QVector<unsigned long long> IEECSMaterialSystem::massReplaceMaterialId(const unsigned long long oldId, const unsigned long long newId)
{
    QVector<unsigned long long> result;

    for(int i = 1; i < data.materialId.size(); i++)
    {
        if(data.materialId[i] == oldId)
        {
            this->setMaterialId(i, newId);
            result.append(i);
        }
    }

    return result;
}

QVector<unsigned long long> IEECSMaterialSystem::massPurgeMaterialId(const unsigned long long idToPurge)
{
    QVector<unsigned long long> result;

    for(int i = 1; i < data.materialId.size(); i++)
    {
        if(data.materialId[i] == idToPurge)
        {
            this->setMaterialId(i, 0);
            result.append(i);
        }
    }

    return result;
}

IEMaterial* IEECSMaterialSystem::getAttachedMaterial(const int index)
{
    if(!indexBoundCheck(index))
        return nullptr;

    return materialManager->value(data.materialId[index]);
}

unsigned long long IEECSMaterialSystem::getMaterialId(const int index)
{
    if(!indexBoundCheck(index))
        return data.materialId[0];

    return data.materialId[index];
}

void IEECSMaterialSystem::setMaterialId(const int index, const unsigned long long val)
{
    if(!indexBoundCheck(index))
        return;

    data.materialId[index] = val;
}
