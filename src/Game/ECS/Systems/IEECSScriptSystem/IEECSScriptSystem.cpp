#include "IEECSScriptSystem.h"
#include "GameStartEvent.h"
#include "ECSOnUpdateEvent.h"
#include "IEScriptEngine.h"
#include "IEHash.h"

IEECSScriptSystem::IEECSScriptSystem() :
    IEECSSystem(),
    data(), scriptEngine(nullptr)
{
    IEECSScriptSystem::attach(IEEntity(-1));
}

IEECSScriptSystem::~IEECSScriptSystem()
{
    removeAll();
    scriptEngine = nullptr;
}

void IEECSScriptSystem::startup(const GameStartEvent& event)
{
    scriptEngine = event.getScriptEngine();

    initAllScripts();
    deserializeScripts();
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

void IEECSScriptSystem::onUpdateFrame(ECSOnUpdateEvent*)
{
    for(int i = 1; i < entityMap.size(); i++)
    {
        foreach(auto& id, data.awakenedScripts[i])
        {
            data.scriptCollection[i][id]->update();
        }
    }
}

void IEECSScriptSystem::initAllScripts()
{
    for(int i = 1; i < entityMap.size(); i++)
    {
        foreach(auto* script, data.scriptCollection[i])
        {
            initalizeScript(i, script->getId());
        }
    }
}

void IEECSScriptSystem::startAllScripts()
{
    for(int i = 1; i < entityMap.size(); i++)
    {
        foreach(auto* script, data.scriptCollection[i])
        {
            startScript(i, script->getId());
        }
    }
}

bool IEECSScriptSystem::initalizeScript(const int index, const unsigned long long id)
{
    if(!isScriptAttached(index, id))
        return false;

    return data.scriptCollection[index][id]->initalize(scriptEngine->getLua());
}

void IEECSScriptSystem::startScript(const int index, const unsigned long long id)
{
    if(!isScriptValid(index, id))
        return;

    data.scriptCollection[index][id]->start(data.entity[index]);
    data.awakenedScripts[index].insert(id);
}

void IEECSScriptSystem::wakeScript(const int index, const unsigned long long id)
{
    if(!isScriptValid(index, id))
        return;

    data.sleepingScripts[index].remove(id);
    data.awakenedScripts[index].insert(id);

    data.scriptCollection[index][id]->wake();
}

void IEECSScriptSystem::sleepScript(const int index, const unsigned long long id)
{
    if(!isScriptValid(index, id))
        return;

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

void IEECSScriptSystem::addScript(const int index, IEEntityScript* script)
{
    if(!indexBoundCheck(index))
    {
        delete script;
        return;
    }

    if(isScriptAttached(index, script->getId()))
    {
        delete script;
        return;
    }

    data.scriptCollection[index][script->getId()] = script;
}

void IEECSScriptSystem::removeScript(const int index, const unsigned long long id)
{
    if(!indexBoundCheck(index))
        return;

    if(!isScriptAttached(index, id))
        return;

    auto temp = data.scriptCollection[index][id];

    data.scriptCollection[index].remove(id);
    data.sleepingScripts[index].remove(id);
    data.awakenedScripts[index].remove(id);

    delete temp;
}

bool IEECSScriptSystem::isScriptAttached(const int index, const unsigned long long id)
{
    if(!indexBoundCheck(index))
        return false;

    return data.scriptCollection[index].contains(id);
}

bool IEECSScriptSystem::isScriptValid(const int index, const unsigned long long id)
{
    if(!isScriptAttached(index, id))
        return false;

    return data.scriptCollection[index][id]->getIsValid();
}

IEScript* IEECSScriptSystem::getScript(const int index, const unsigned long long id)
{
    if(!isScriptAttached(index, id))
        return nullptr;

    return data.scriptCollection[index][id];
}

IEScript* IEECSScriptSystem::getScript(const int index, const QString& name)
{
    const unsigned long long id = IEHash::Compute(name);
    if(!isScriptAttached(index, id))
        return nullptr;

    return data.scriptCollection[index][id];
}

void IEECSScriptSystem::deserializeScripts()
{
    for(int i = 1; i < entityMap.size(); i++)
    {
        foreach(auto* script, data.scriptCollection[i])
        {
            script->dataToScript();
        }
    }
}

void IEECSScriptSystem::removeAll()
{
    for(int i = 1; i < entityMap.size(); i++)
    {
        QMapIterator<unsigned long long, IEEntityScript*> it(data.scriptCollection[i]);
        while(it.hasNext())
        {
            it.next();

            auto* temp = it.value();
            data.scriptCollection[i][it.key()] = nullptr;
            delete temp;
        }
    }
}

void IEECSScriptSystem::removeAll(const int index)
{
    if(!indexBoundCheck(index))
        return;

    QMapIterator<unsigned long long, IEEntityScript*> it(data.scriptCollection[index]);
    while(it.hasNext())
    {
        it.next();

        auto* temp = it.value();
        data.scriptCollection[index][it.key()] = nullptr;
        delete temp;
    }
}
