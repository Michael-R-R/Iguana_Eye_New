#include "IEECSScriptSystem.h"
#include "IEGame.h"
#include "IEScriptEngine.h"
#include "IEPhysicsEngine.h"
#include "IESimulationCallback.h"
#include "IEHash.h"

IEECSScriptSystem::IEECSScriptSystem(QObject* parent) :
    IEECSSystem(parent),
    data()
{
    IEECSScriptSystem::attach(IEEntity(-1));
}

IEECSScriptSystem::~IEECSScriptSystem()
{

}

int IEECSScriptSystem::attach(const IEEntity entity)
{
    if(doesExist(entity))
        return -1;

    const int index = entityMap.size();

    entityMap[entity] = index;

    data.entity.append(entity);
    data.scripts.append(QMap<unsigned long long, IEScript*>());
    data.sleepingScripts.append(QSet<unsigned long long>());
    data.awakenedScripts.append(QSet<unsigned long long>());

    return index;
}

bool IEECSScriptSystem::detach(const IEEntity entity)
{
    if(!doesExist(entity))
        return false;

    const int indexToRemove = entityMap[entity];

    removeAll(indexToRemove);

    const int lastIndex = entityMap.size() - 1;
    const IEEntity lastEntity = data.entity[lastIndex];

    data.entity[indexToRemove] = data.entity[lastIndex];
    data.scripts[indexToRemove] = data.scripts[lastIndex];
    data.sleepingScripts[indexToRemove] = data.sleepingScripts[lastIndex];
    data.awakenedScripts[indexToRemove] = data.awakenedScripts[lastIndex];

    data.entity.removeLast();
    data.scripts.removeLast();
    data.sleepingScripts.removeLast();
    data.awakenedScripts.removeLast();

    entityMap[lastEntity] = indexToRemove;
    entityMap.remove(entity);

    return true;
}

void IEECSScriptSystem::startUp(const IEGame& game)
{
    auto* physicsEngine = game.getPhysicsEngine();
    auto& simCallback = physicsEngine->getSimulationCallback();
    connect(&simCallback, &IESimulationCallback::onTriggerEnter, this, &IEECSScriptSystem::callOnTriggerEnter);
    connect(&simCallback, &IESimulationCallback::onTriggerLeave, this, &IEECSScriptSystem::callOnTriggerLeave);

    scriptEngine = game.getScriptEngine();
}

void IEECSScriptSystem::onUpdateFrame()
{
    for(int i = 1; i < entityMap.size(); i++)
    {
        foreach(auto& id, data.awakenedScripts[i])
        {
            data.scripts[i][id]->update();
        }
    }
}

void IEECSScriptSystem::wakeScript(const int index, const unsigned long long id)
{
    data.sleepingScripts[index].remove(id);
    data.awakenedScripts[index].insert(id);

    data.scripts[index][id]->wake();
}

void IEECSScriptSystem::sleepScript(const int index, const unsigned long long id)
{
    data.awakenedScripts[index].remove(id);
    data.sleepingScripts[index].insert(id);

    data.scripts[index][id]->sleep();
}

void IEECSScriptSystem::clearSleepingScripts()
{
    for(int i = 1; i < entityMap.size(); i++)
    {
        data.sleepingScripts[i].clear();
    }
}

void IEECSScriptSystem::clearAwakenScripts()
{
    for(int i = 1; i < entityMap.size(); i++)
    {
        data.awakenedScripts[i].clear();
    }
}

void IEECSScriptSystem::attachScript(const int index, IEScript* script)
{
    if(hasScript(index, script->getId()))
        return;

    delete data.scripts[index][script->getId()];
    data.scripts[index][script->getId()] = script;
}

void IEECSScriptSystem::removeScript(const int index, const unsigned long long id)
{
    if(!hasScript(index, id))
        return;

    delete data.scripts[index][id];
    data.scripts[index].remove(id);
    data.sleepingScripts[index].remove(id);
    data.awakenedScripts[index].remove(id);
}

bool IEECSScriptSystem::hasScript(const int index, const unsigned long long id)
{
    if(!indexBoundCheck(index))
        return false;

    return data.scripts[index].contains(id);
}

IEScript* IEECSScriptSystem::getScript(const int index, const unsigned long long id)
{
    if(!hasScript(index, id))
        return nullptr;

    return data.scripts[index][id];
}

IEScript* IEECSScriptSystem::getScript(const int index, const char* name)
{
    const unsigned long long id = IEHash::Compute(name);
    if(!hasScript(index, id))
        return nullptr;

    return data.scripts[index][id];
}

void IEECSScriptSystem::deserializeScripts()
{
    for(int i = 1; i < entityMap.size(); i++)
    {
        foreach(auto script, data.scripts[i])
        {
            script->dataTo();
        }
    }
}

void IEECSScriptSystem::removeAll()
{
    for(int i = 1; i < entityMap.size(); i++)
    {
        data.scripts[i].clear();
    }
}

void IEECSScriptSystem::removeAll(const int index)
{
    if(!indexBoundCheck(index))
        return;

    data.scripts[index].clear();
}

void IEECSScriptSystem::callOnTriggerEnter(const IEEntity& triggerEntity, const IEEntity& otherEntity)
{
    const int triggerIndex = this->lookUpIndex(triggerEntity);
    if(!indexBoundCheck(triggerIndex))
        return;

    foreach(auto i, data.scripts[triggerIndex])
    {
        i->onTriggerEnter(otherEntity);
    }
}

void IEECSScriptSystem::callOnTriggerLeave(const IEEntity& triggerEntity, const IEEntity& otherEntity)
{
    const int triggerIndex = this->lookUpIndex(triggerEntity);
    if(!indexBoundCheck(triggerIndex))
        return;

    foreach(auto i, data.scripts[triggerIndex])
    {
        i->onTriggerLeave(otherEntity);
    }
}

QDataStream& IEECSScriptSystem::serialize(QDataStream& out, const Serializable& obj) const
{
    const auto& system = static_cast<const IEECSScriptSystem&>(obj);

    out << system.entityMap << system.data;

    return out;
}

QDataStream& IEECSScriptSystem::deserialize(QDataStream& in, Serializable& obj)
{
    auto& system = static_cast<IEECSScriptSystem&>(obj);

    in >> system.entityMap >> system.data;

    system.deserializeScripts();

    return in;
}
