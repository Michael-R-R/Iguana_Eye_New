#include "IEECSScriptSystem.h"
#include "ApplicationWindow.h"
#include "IEGame.h"
#include "IEScriptEngine.h"
#include "IEPhysicsEngine.h"
#include "IESimulationCallback.h"
#include "ECSOnUpdateEvent.h"
#include "IEHash.h"

IEECSScriptSystem::IEECSScriptSystem(QObject* parent) :
    IEECSSystem(parent),
    data()
{
    IEECSScriptSystem::attach(IEEntity(-1));

    auto* game = ApplicationWindow::instance().getGame();
    auto* physicsEngine = game->getPhysicsEngine();
    auto& simCallback = physicsEngine->getSimulationCallback();
    connect(&simCallback, &IESimulationCallback::onTriggerEnter, this, &IEECSScriptSystem::callOnTriggerEnter);
    connect(&simCallback, &IESimulationCallback::onTriggerLeave, this, &IEECSScriptSystem::callOnTriggerLeave);
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
    data.scriptCollection.append(QMap<unsigned long long, IEEntityScript*>());
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
    data.scriptCollection[indexToRemove] = data.scriptCollection[lastIndex];
    data.sleepingScripts[indexToRemove] = data.sleepingScripts[lastIndex];
    data.awakenedScripts[indexToRemove] = data.awakenedScripts[lastIndex];

    data.entity.removeLast();
    data.scriptCollection.removeLast();
    data.sleepingScripts.removeLast();
    data.awakenedScripts.removeLast();

    entityMap[lastEntity] = indexToRemove;
    entityMap.remove(entity);

    return true;
}

void IEECSScriptSystem::onUpdateFrame(ECSOnUpdateEvent&)
{
    for(int i = 1; i < entityMap.size(); i++)
    {
        foreach(auto& id, data.awakenedScripts[i])
        {
            data.scriptCollection[i][id]->update();
        }
    }
}

void IEECSScriptSystem::initalize()
{
    auto* game = ApplicationWindow::instance().getGame();
    auto* scriptEngine = game->getScriptEngine();
    auto& lua = scriptEngine->getLua();

    for(int i = 1; i < entityMap.size(); i++)
    {
        foreach(auto& script, data.scriptCollection[i])
        {
            script->initalize(lua);
            script->start(data.entity[i]);
            data.awakenedScripts[i].insert(script->getId());
        }
    }
}

void IEECSScriptSystem::reset()
{
    clearSleepingScripts();
    clearAwakenScripts();
}

void IEECSScriptSystem::wakeScript(const int index, const unsigned long long id)
{
    data.sleepingScripts[index].remove(id);
    data.awakenedScripts[index].insert(id);

    data.scriptCollection[index][id]->wake();
}

void IEECSScriptSystem::sleepScript(const int index, const unsigned long long id)
{
    data.awakenedScripts[index].remove(id);
    data.sleepingScripts[index].insert(id);

    data.scriptCollection[index][id]->sleep();
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

void IEECSScriptSystem::attachScript(const int index, IEEntityScript* script)
{
    if(hasScript(index, script->getId()))
        return;

    delete data.scriptCollection[index][script->getId()];
    data.scriptCollection[index][script->getId()] = script;
}

void IEECSScriptSystem::removeScript(const int index, const unsigned long long id)
{
    if(!hasScript(index, id))
        return;

    delete data.scriptCollection[index][id];
    data.scriptCollection[index].remove(id);
    data.sleepingScripts[index].remove(id);
    data.awakenedScripts[index].remove(id);
}

bool IEECSScriptSystem::hasScript(const int index, const unsigned long long id)
{
    if(!indexBoundCheck(index))
        return false;

    return data.scriptCollection[index].contains(id);
}

IEEntityScript* IEECSScriptSystem::getScript(const int index, const unsigned long long id)
{
    if(!hasScript(index, id))
        return nullptr;

    return data.scriptCollection[index][id];
}

IEEntityScript* IEECSScriptSystem::getScript(const int index, const char* name)
{
    const unsigned long long id = IEHash::Compute(name);
    if(!hasScript(index, id))
        return nullptr;

    return data.scriptCollection[index][id];
}

void IEECSScriptSystem::deserializeScripts()
{
    for(int i = 1; i < entityMap.size(); i++)
    {
        foreach(auto script, data.scriptCollection[i])
        {
            script->dataToScript();
        }
    }
}

void IEECSScriptSystem::removeAll()
{
    for(int i = 1; i < entityMap.size(); i++)
    {
        data.scriptCollection[i].clear();
    }
}

void IEECSScriptSystem::removeAll(const int index)
{
    if(!indexBoundCheck(index))
        return;

    data.scriptCollection[index].clear();
}

void IEECSScriptSystem::callOnTriggerEnter(const IEEntity& triggerEntity, const IEEntity& otherEntity)
{
    const int triggerIndex = this->lookUpIndex(triggerEntity);
    if(!indexBoundCheck(triggerIndex))
        return;

    foreach(auto i, data.scriptCollection[triggerIndex])
    {
        i->onTriggerEnter(otherEntity);
    }
}

void IEECSScriptSystem::callOnTriggerLeave(const IEEntity& triggerEntity, const IEEntity& otherEntity)
{
    const int triggerIndex = this->lookUpIndex(triggerEntity);
    if(!indexBoundCheck(triggerIndex))
        return;

    foreach(auto i, data.scriptCollection[triggerIndex])
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
