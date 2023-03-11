#include "IEECSScriptSystem.h"
#include "GameStartEvent.h"
#include "ECSOnUpdateEvent.h"
#include "IEScriptEngine.h"

IEECSScriptSystem::IEECSScriptSystem() :
    IEECSSystem(),
    data(), scriptEngine(nullptr)
{
    IEECSScriptSystem::attach(IEEntity(-1));
}

IEECSScriptSystem::~IEECSScriptSystem()
{
    clearAll();
    scriptEngine = nullptr;
}

void IEECSScriptSystem::startup(const GameStartEvent& event)
{
    scriptEngine = event.getScriptEngine();

    createAllScripts();
}

int IEECSScriptSystem::attach(const IEEntity entity)
{
    if(doesExist(entity))
        return -1;

    const int index = entityMap.size();

    entityMap[entity] = index;

    data.entity.append(entity);
    data.scriptCollection.append(QMap<unsigned long long, IEEntityScript*>());
    data.disabledScripts.append(QSet<unsigned long long>());
    data.activeScripts.append(QSet<unsigned long long>());

    return index;
}

bool IEECSScriptSystem::detach(const IEEntity entity)
{
    if(!doesExist(entity))
        return false;

    const int indexToRemove = entityMap[entity];

    clearAtIndex(indexToRemove);

    const int lastIndex = entityMap.size() - 1;
    const IEEntity lastEntity = data.entity[lastIndex];

    data.entity[indexToRemove] = data.entity[lastIndex];
    data.scriptCollection[indexToRemove] = data.scriptCollection[lastIndex];
    data.disabledScripts[indexToRemove] = data.disabledScripts[lastIndex];
    data.activeScripts[indexToRemove] = data.activeScripts[lastIndex];

    data.entity.removeLast();
    data.scriptCollection.removeLast();
    data.disabledScripts.removeLast();
    data.activeScripts.removeLast();

    entityMap[lastEntity] = indexToRemove;
    entityMap.remove(entity);

    return true;
}

void IEECSScriptSystem::onUpdateFrame(ECSOnUpdateEvent*)
{
    for(int i = 1; i < entityMap.size(); i++)
    {
        foreach(auto& id, data.activeScripts[i])
        {
            const int entityId = data.entity[i].getId();
            data.scriptCollection[i][id]->update(entityId);
        }
    }
}

void IEECSScriptSystem::createAllScripts()
{
    auto& lua = scriptEngine->getLua();

    for(int i = 1; i < entityMap.size(); i++)
    {
        foreach(auto script, data.scriptCollection[i])
        {
            script->create(lua);
            script->dataToScript();
        }
    }
}

void IEECSScriptSystem::enableAllScripts()
{
    for(int i = 1; i < entityMap.size(); i++)
    {
        foreach(auto script, data.scriptCollection[i])
        {
            this->enableScript(i, script->getId());
        }
    }
}

void IEECSScriptSystem::disableAllScripts()
{
    for(int i = 1; i < entityMap.size(); i++)
    {
        foreach(auto script, data.scriptCollection[i])
        {
            this->disableScript(i, script->getId());
        }
    }
}

void IEECSScriptSystem::enableScript(const int index, const unsigned long long id)
{
    if(!indexBoundCheck(index))
        return;

    data.disabledScripts[index].remove(id);
    data.activeScripts[index].insert(id);

    const int entityId = data.entity[index].getId();
    auto* script = data.scriptCollection[index][id];
    script->start(entityId);
}

void IEECSScriptSystem::disableScript(const int index, const unsigned long long id)
{
    if(!indexBoundCheck(index))
        return;

    data.activeScripts[index].remove(id);
    data.disabledScripts[index].insert(id);

    const int entityId = data.entity[index].getId();
    auto* script = data.scriptCollection[index][id];
    script->sleep(entityId);
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
    data.disabledScripts[index].remove(id);
    data.activeScripts[index].remove(id);

    delete temp;
}

bool IEECSScriptSystem::isScriptAttached(const int index, const unsigned long long id)
{
    if(!indexBoundCheck(index))
        return false;

    return data.scriptCollection[index].contains(id);
}

void IEECSScriptSystem::clearAll()
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

void IEECSScriptSystem::clearAtIndex(const int index)
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
