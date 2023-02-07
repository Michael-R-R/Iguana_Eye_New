#include "IENameManager.h"
#include "GameStartEvent.h"
#include "IEHash.h"

IENameManager::IENameManager(QObject* parent) :
    IEManager(parent)
{

}

IENameManager::~IENameManager()
{

}

void IENameManager::startup(const GameStartEvent& event)
{
    // Not used
}

void IENameManager::shutdown()
{
    resourceContainer->clear();
}

bool IENameManager::add(const unsigned long long key, QString* value)
{
    if(!IEManager::add(key, value))
        return false;

    emit added(key);
    return true;
}

bool IENameManager::remove(const unsigned long long key)
{
    if(!IEManager::remove(key))
        return false;

    emit removed(key);
    return true;
}

bool IENameManager::changeKey(const unsigned long long oldKey, const unsigned long long newKey)
{
    if(!IEManager::changeKey(oldKey, newKey))
        return false;

    emit keyChanged(oldKey, newKey);
    return true;
}

std::tuple<unsigned long long, QString> IENameManager::hashString(const QString& value) const
{
    QString temp = value;

    int counter = 0;
    unsigned long long hash = IEHash::Compute(temp);

    while(resourceContainer->doesExist(hash))
    {
        temp = value + "_" + QString::number(counter);
        counter++;
        hash = IEHash::Compute(temp);
    }

    return std::make_tuple(hash, temp);
}

QDataStream& operator<<(QDataStream& out, const IENameManager& manager)
{
    out << *manager.getResourceContainer();

    return out;
}

QDataStream& operator>>(QDataStream& in, IENameManager& manager)
{
    IEResourceContainer<QString>* container = manager.getResourceContainer();

    in >> *container;

    manager.setResourceContainer(container);

    return in;
}

