#include "IEECSNameSystem.h"
#include "GameStartEvent.h"
#include "ECSOnUpdateEvent.h"
#include "IEHash.h"

IEECSNameSystem::IEECSNameSystem() :
    IEECSSystem(),
    data(),
    nameMap(),
    tagNameMap(), tagEntityMap()
{
    nameMap[0] = "Invalid";
    tagNameMap[0] = "Invalid";
    tagEntityMap[0] = QVector<IEEntity>();
    IEECSNameSystem::attach(IEEntity(-1));
}

void IEECSNameSystem::startup(const GameStartEvent&)
{
    // Not used
}

int IEECSNameSystem::attach(const IEEntity entity)
{
    if(doesExist(entity))
        return -1;

    // Hash a default name
    unsigned long long hash = 0;
    QString name = "";
    std::tie(hash, name) = this->hashString("Default");
    nameMap[hash] = name;

    int index = entityMap.size();
    entityMap[entity] = index;

    data.entity.append(entity);
    data.nameKey.append(hash);
    data.tagKey.append(0);
    data.tagIndex.append(-1);

    return index;
}

bool IEECSNameSystem::detach(const IEEntity entity)
{
    if(!doesExist(entity))
        return false;

    const int indexToRemove = entityMap[entity];

    this->removeName(data.nameKey[indexToRemove]);
    this->clearEntityTag(indexToRemove);

    const int lastIndex = entityMap.size() - 1;
    const IEEntity lastEntity = data.entity[lastIndex];

    data.entity[indexToRemove] = data.entity[lastIndex];
    data.nameKey[indexToRemove] = data.nameKey[lastIndex];
    data.tagKey[indexToRemove] = data.tagKey[lastIndex];
    data.tagIndex[indexToRemove] = data.tagIndex[lastIndex];

    data.entity.removeLast();
    data.nameKey.removeLast();
    data.tagKey.removeLast();
    data.tagIndex.removeLast();

    entityMap[lastEntity] = indexToRemove;
    entityMap.remove(entity);

    return true;
}

void IEECSNameSystem::onUpdateFrame(ECSOnUpdateEvent*)
{
    // Not used
}

void IEECSNameSystem::addNameTag(const QString& name)
{
    unsigned long long hash = IEHash::Compute(name);
    if(tagNameMap.contains(hash))
        return;

    tagNameMap[hash] = name;
    tagEntityMap[hash] = QVector<IEEntity>();
}

void IEECSNameSystem::clearNameTag(const QString& name)
{
    unsigned long long hash = IEHash::Compute(name);
    if(!tagNameMap.contains(hash))
        return;

    foreach(auto entity, tagEntityMap[hash])
    {
        const int index = this->lookUpIndex(entity);
        data.tagKey[index] = 0;
        data.tagIndex[index] = -1;
    }

    tagNameMap.remove(hash);
    tagEntityMap.remove(hash);
}

void IEECSNameSystem::clearEntityTag(const int index)
{
    if(!indexBoundCheck(index))
        return;

    const unsigned long long key = data.tagKey[index];
    const int tagIndex = data.tagIndex[index];
    this->removeEntityTag(key, tagIndex);

    data.tagKey[index] = 0;
    data.tagIndex[index] = -1;
}

QVector<IEEntity> IEECSNameSystem::getEntityTagList(const QString& name) const
{
    const unsigned long long hash = IEHash::Compute(name);
    if(!tagEntityMap.contains(hash))
        return QVector<IEEntity>();

    return tagEntityMap[hash];
}

unsigned long long IEECSNameSystem::getNameKey(const int index) const
{
    if(!indexBoundCheck(index))
        return data.nameKey[0];

    return data.nameKey[index];
}

unsigned long long IEECSNameSystem::getTagKey(const int index) const
{
    if(!indexBoundCheck(index))
        return data.tagKey[0];

    return data.tagKey[index];
}

int IEECSNameSystem::getTagIndex(const int index) const
{
    if(!indexBoundCheck(index))
        return data.tagIndex[0];

    return data.tagIndex[index];
}

QString IEECSNameSystem::getName(const int index) const
{
    if(!indexBoundCheck(index))
        return nameMap[0];

    return nameMap[data.nameKey[index]];
}

QString IEECSNameSystem::getTagName(const int index) const
{
    if(!indexBoundCheck(index))
        return tagNameMap[0];

    return tagNameMap[data.tagKey[index]];
}

void IEECSNameSystem::setName(const int index, const QString& val)
{
    if(!indexBoundCheck(index))
        return;

    unsigned long long hash = 0;
    QString name = "";
    std::tie(hash, name) = this->hashString(val);

    this->removeName(data.nameKey[index]);

    data.nameKey[index] = hash;
    nameMap[hash] = name;
}

void IEECSNameSystem::setTag(const int index, const QString& val)
{
    if(!indexBoundCheck(index))
        return;

    if(val.isEmpty())
    {
        clearEntityTag(index);
        return;
    }

    // Clear existing tag
    this->clearEntityTag(index);

    unsigned long long hash = IEHash::Compute(val);
    if(tagNameMap.contains(hash))
    {
        // Add entity to existing tag map
        data.tagKey[index] = hash;
        data.tagIndex[index] = tagEntityMap[hash].size();
        tagEntityMap[hash].append(data.entity[index]);
    }
    else
    {
        // Create new tag map and add entity
        tagNameMap[hash] = val;
        tagEntityMap[hash] = QVector<IEEntity>();

        data.tagKey[index] = hash;
        data.tagIndex[index] = tagEntityMap[hash].size();
        tagEntityMap[hash].append(data.entity[index]);
    }
}

std::tuple<unsigned long long, QString> IEECSNameSystem::hashString(const QString& value)
{
    QString temp = value;

    int counter = 0;
    unsigned long long hash = IEHash::Compute(temp);

    while(nameMap.contains(hash))
    {
        temp = value + "_" + QString::number(counter);
        counter++;
        hash = IEHash::Compute(temp);
    }

    return std::make_tuple(hash, temp);
}

void IEECSNameSystem::removeName(const unsigned long long key)
{
    nameMap.remove(key);
}

void IEECSNameSystem::removeNameTag(const unsigned long long key)
{
    tagNameMap.remove(key);
}

void IEECSNameSystem::removeEntityTag(const unsigned long long key, const int tagIndex)
{
    if(key == 0)
        return;

    if(tagIndex < 0 || tagIndex > tagEntityMap[key].size())
        return;

    const int lastIndex = tagEntityMap[key].size() - 1;
    tagEntityMap[key][tagIndex] = tagEntityMap[key][lastIndex];

    const int entityIndex = this->lookUpIndex(tagEntityMap[key][tagIndex]);
    data.tagIndex[entityIndex] = tagIndex;

    tagEntityMap[key].removeLast();
}

QDataStream& IEECSNameSystem::serialize(QDataStream& out, const Serializable& obj) const
{
    const auto& system = static_cast<const IEECSNameSystem&>(obj);

    out << system.entityMap << system.data << system.nameMap
        << system.tagNameMap << system.tagEntityMap;

    return out;
}

QDataStream& IEECSNameSystem::deserialize(QDataStream& in, Serializable& obj)
{
    auto& system = static_cast<IEECSNameSystem&>(obj);

    in >> system.entityMap >> system.data >> system.nameMap
       >> system.tagNameMap >> system.tagEntityMap;

    return in;
}
