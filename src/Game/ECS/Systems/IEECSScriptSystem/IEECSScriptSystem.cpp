#include "IEECSScriptSystem.h"
#include "GameStartEvent.h"
#include "ECSOnUpdateEvent.h"

IEECSScriptSystem::IEECSScriptSystem() :
    IEECSSystem(),
    data()
{
    IEECSScriptSystem::attach(IEEntity(-1));
}

void IEECSScriptSystem::startup(const GameStartEvent&)
{

}

int IEECSScriptSystem::attach(const IEEntity entity)
{
    if(doesExist(entity))
        return -1;

    const int index = entityMap.size();

    entityMap[entity] = index;

    data.entity.append(entity);
    data.scriptCollection.append(QMap<unsigned long long, IEScript>());
    data.disabledScripts.append(QSet<unsigned long long>());
    data.activeScripts.append(QSet<unsigned long long>());

    return index;
}

bool IEECSScriptSystem::detach(const IEEntity entity)
{
    if(!doesExist(entity))
        return false;

    const int indexToRemove = entityMap[entity];

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
            data.scriptCollection[i][id].update();
        }
    }
}

void IEECSScriptSystem::addScript(const int index, const IEScript& script)
{
    if(!indexBoundCheck(index))
        return;

    if(isScriptAttached(index, script.getId()))
        return;

    data.scriptCollection[index][script.getId()] = script;
}

void IEECSScriptSystem::removeScript(const int index, const unsigned long long id)
{
    if(!indexBoundCheck(index))
        return;

    if(!isScriptAttached(index, id))
        return;

    data.scriptCollection[index].remove(id);
    data.disabledScripts[index].remove(id);
    data.activeScripts[index].remove(id);
}

void IEECSScriptSystem::enableScript(const int index, const unsigned long long id)
{
    if(!indexBoundCheck(index))
        return;

    if(!data.disabledScripts[index].contains(id))
        return;

    data.disabledScripts[index].remove(id);
    data.activeScripts[index].insert(id);

    data.scriptCollection[index][id].start();
}

void IEECSScriptSystem::disableScript(const int index, const unsigned long long id)
{
    if(!indexBoundCheck(index))
        return;

    if(!data.activeScripts[index].contains(id))
        return;

    data.activeScripts[index].remove(id);
    data.disabledScripts[index].insert(id);
}

bool IEECSScriptSystem::isScriptAttached(const int index, const unsigned long long id)
{
    if(!indexBoundCheck(index))
        return false;

    return data.scriptCollection[index].contains(id);
}
