#include "IEECSShaderSystem.h"
#include "IEGame.h"
#include "IEScene.h"
#include "IEShaderManager.h"
#include "ECSOnUpdateEvent.h"

IEECSShaderSystem::IEECSShaderSystem(IEGame& game) :
    IEECSSystem(),
    data(),
    shaderManager(game.getIEScene().getShaderManager())
{
    IEECSShaderSystem::attach(IEEntity(-1));
}

IEECSShaderSystem::~IEECSShaderSystem()
{

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

IEShader* IEECSShaderSystem::getAttachedShader(const int index) const
{
    if(!indexBoundCheck(index))
        return nullptr;

    return shaderManager.value(data.shaderId[index]);
}

unsigned long long IEECSShaderSystem::getShaderId(const int index) const
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

QDataStream& IEECSShaderSystem::serialize(QDataStream& out, const Serializable& obj) const
{
    const auto& system = static_cast<const IEECSShaderSystem&>(obj);

    out << system.entityMap << system.data;

    return out;
}

QDataStream& IEECSShaderSystem::deserialize(QDataStream& in, Serializable& obj)
{
    auto& system = static_cast<IEECSShaderSystem&>(obj);

    in >> system.entityMap >> system.data;

    return in;
}
