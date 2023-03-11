#include "IEECSShaderSystem.h"
#include "GameStartEvent.h"
#include "ECSOnUpdateEvent.h"
#include "IEScene.h"

IEECSShaderSystem::IEECSShaderSystem() :
    IEECSSystem(),
    data(),
    shaderManager(nullptr)
{
    IEECSShaderSystem::attach(IEEntity(-1));
}

IEECSShaderSystem::~IEECSShaderSystem()
{
    shaderManager = nullptr;
}

void IEECSShaderSystem::startup(const GameStartEvent& event)
{
    shaderManager = event.getScene().getShaderManager();
}

int IEECSShaderSystem::attach(const IEEntity entity)
{
    if(doesExist(entity))
        return -1;

    const int index = entityMap.size();

    entityMap[entity] = index;

    data.entity.append(entity);
    data.shaderId.append(0);

    return index;
}

bool IEECSShaderSystem::detach(const IEEntity entity)
{
    if(!doesExist(entity))
        return false;

    const int indexToRemove = entityMap[entity];

    const int lastIndex = entityMap.size() - 1;
    const IEEntity lastEntity = data.entity[lastIndex];

    data.entity[indexToRemove] = data.entity[lastIndex];
    data.shaderId[indexToRemove] = data.shaderId[lastIndex];

    data.entity.removeLast();
    data.entity.removeLast();

    entityMap[lastEntity] = indexToRemove;
    entityMap.remove(entity);

    return true;
}

void IEECSShaderSystem::onUpdateFrame(ECSOnUpdateEvent*)
{
    // Not used
}

QVector<unsigned long long> IEECSShaderSystem::massReplaceShaderId(const unsigned long long oldId, const unsigned long long newId)
{
    QVector<unsigned long long> result;

    for(int i = 1; i < data.shaderId.size(); i++)
    {
        if(data.shaderId[i] == oldId)
        {
            this->setShaderId(i, newId);
            result.append(i);
        }
    }

    return result;
}

QVector<unsigned long long> IEECSShaderSystem::massPurgeShaderId(const unsigned long long idToPurge)
{
    QVector<unsigned long long> result;

    for(int i = 1; i < data.shaderId.size(); i++)
    {
        if(data.shaderId[i] == idToPurge)
        {
            this->setShaderId(i, 0);
            result.append(i);
        }
    }

    return result;
}

IEShader* IEECSShaderSystem::getAttachedShader(const int index)
{
    if(!indexBoundCheck(index))
        return nullptr;

    return shaderManager->getValue(data.shaderId[index]);
}

unsigned long long IEECSShaderSystem::getShaderId(const int index)
{
    if(!indexBoundCheck(index))
        return data.shaderId[0];

    return data.shaderId[index];
}

void IEECSShaderSystem::setShaderId(const int index, const unsigned long long val)
{
    if(!indexBoundCheck(index))
        return;

    data.shaderId[index] = val;
}
