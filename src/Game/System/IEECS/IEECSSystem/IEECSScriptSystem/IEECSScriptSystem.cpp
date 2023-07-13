#include "IEECSScriptSystem.h"
#include "IEGame.h"
#include "IEScriptEngine.h"
#include "IEPhysicsEngine.h"
#include "IESimulationCallback.h"
#include "IEHash.h"

IEECSScriptSystem::IEECSScriptSystem(QObject* parent) :
    IEECSSystem(typeid(IEECSScriptSystem).hash_code(), parent),
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
    data.scripts.append(QHash<uint64_t, IEScript*>());
    data.sleepingScripts.append(QSet<uint64_t>());
    data.awakenedScripts.append(QSet<uint64_t>());

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
    auto* physicsEngine = game.getSystem<IEPhysicsEngine>();
    auto& simCallback = physicsEngine->getSimulationCallback();
    connect(&simCallback, &IESimulationCallback::onTriggerEnter, this, &IEECSScriptSystem::callOnTriggerEnter);
    connect(&simCallback, &IESimulationCallback::onTriggerLeave, this, &IEECSScriptSystem::callOnTriggerLeave);

    sEngine = game.getSystem<IEScriptEngine>();
}

void IEECSScriptSystem::shutdown(const IEGame& game)
{
    removeAll();

    auto* physicsEngine = game.getSystem<IEPhysicsEngine>();
    auto& simCallback = physicsEngine->getSimulationCallback();
    disconnect(&simCallback, &IESimulationCallback::onTriggerEnter, this, &IEECSScriptSystem::callOnTriggerEnter);
    disconnect(&simCallback, &IESimulationCallback::onTriggerLeave, this, &IEECSScriptSystem::callOnTriggerLeave);

    sEngine = nullptr;
}

void IEECSScriptSystem::onDeserialize(const IEGame&)
{
    removeAll();
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

void IEECSScriptSystem::initAll()
{
    for(int i = 1; i < data.scripts.size(); i++)
    {
        foreach(auto* j, data.scripts[i])
        {
            j->init(sEngine->getLua(), data.entity[i]);
        }
    }
}

void IEECSScriptSystem::startAll()
{
    for(int i = 1; i < data.scripts.size(); i++)
    {
        foreach(auto* j, data.scripts[i])
        {
            data.sleepingScripts[i].remove(id);
            data.awakenedScripts[i].insert(id);

            j->start();
        }
    }
}

void IEECSScriptSystem::wakeAll()
{
    for(int i = 1; i < data.scripts.size(); i++)
    {
        foreach(auto* j, data.scripts[i])
        {
            data.sleepingScripts[i].remove(id);
            data.awakenedScripts[i].insert(id);

            j->wake();
        }
    }
}

void IEECSScriptSystem::sleepAll()
{
    for(int i = 1; i < data.scripts.size(); i++)
    {
        foreach(auto* j, data.scripts[i])
        {
            data.sleepingScripts[i].insert(id);
            data.awakenedScripts[i].remove(id);

            j->sleep();
        }
    }
}

void IEECSScriptSystem::init(const int index, const uint64_t id)
{
    if(!hasScript(index, id))
        return;

    data.scripts[index][id]->init(sEngine->getLua(), data.entity[index]);
}

void IEECSScriptSystem::start(const int index, const uint64_t id)
{
    if(!hasScript(index, id))
        return;

    data.sleepingScripts[index].remove(id);
    data.awakenedScripts[index].insert(id);

    data.scripts[index][id]->start();
}

void IEECSScriptSystem::wake(const int index, const uint64_t id)
{
    if(!hasScript(index, id))
        return;

    data.sleepingScripts[index].remove(id);
    data.awakenedScripts[index].insert(id);

    data.scripts[index][id]->wake();
}

void IEECSScriptSystem::sleep(const int index, const uint64_t id)
{
    if(!hasScript(index, id))
        return;

    data.awakenedScripts[index].remove(id);
    data.sleepingScripts[index].insert(id);

    data.scripts[index][id]->sleep();
}

void IEECSScriptSystem::attach(const int index, IEScript* script)
{
    if(hasScript(index, script->getID()))
        return;

    delete data.scripts[index][script->getID()];
    data.scripts[index][script->getID()] = script;
}

void IEECSScriptSystem::remove(const int index, const uint64_t id)
{
    if(!hasScript(index, id))
        return;

    delete data.scripts[index][id];
    data.scripts[index].remove(id);
    data.sleepingScripts[index].remove(id);
    data.awakenedScripts[index].remove(id);
}

bool IEECSScriptSystem::hasScript(const int index, const uint64_t id)
{
    if(!indexBoundCheck(index))
        return false;

    return data.scripts[index].contains(id);
}

IEScript* IEECSScriptSystem::getScript(const int index, const uint64_t id)
{
    if(!hasScript(index, id))
        return nullptr;

    return data.scripts[index][id];
}

IEScript* IEECSScriptSystem::getScript(const int index, const char* name)
{
    const uint64_t id = IEHash::Compute(name);
    if(!hasScript(index, id))
        return nullptr;

    return data.scripts[index][id];
}

void IEECSScriptSystem::cacheScripts()
{
    for(int i = 1; i < entityMap.size(); i++)
    {
        foreach(auto script, data.scripts[i])
        {
            script->dataFrom();
        }
    }
}

void IEECSScriptSystem::decacheScripts()
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
    for(int i = 0; i < data.scripts.size(); i++)
    {
        foreach (auto* i, data.scripts[i])
        {
            delete i;
            i = nullptr;
        }

        data.scripts[i].clear();
    }
}

void IEECSScriptSystem::removeAll(const int index)
{
    if(!indexBoundCheck(index))
        return;

    foreach (auto* i, data.scripts[index])
    {
        delete i;
        i = nullptr;
    }

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

QDataStream& IEECSScriptSystem::serialize(QDataStream& out, const IESerializable& obj) const
{
    const auto& system = static_cast<const IEECSScriptSystem&>(obj);

    out << system.entityMap << system.data;

    const_cast<IEECSScriptSystem&>(system).cacheScripts();

    return out;
}

QDataStream& IEECSScriptSystem::deserialize(QDataStream& in, IESerializable& obj)
{
    auto& system = static_cast<IEECSScriptSystem&>(obj);

    in >> system.entityMap >> system.data;

    system.initAll();
    system.decacheScripts();

    return in;
}
