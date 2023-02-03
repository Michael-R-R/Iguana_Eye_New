#include "IENameManager.h"
#include "IEHash.h"

IENameManager::IENameManager(QObject* parent) :
    IEObject(parent),
    resourceContainer(new IEResourceContainer<QString>(this))
{

}

IENameManager::~IENameManager()
{

}

bool IENameManager::add(const unsigned long long key, QString* value)
{
    if(!resourceContainer->add(key, value))
        return false;

    emit added(key);

    return true;
}

bool IENameManager::remove(const unsigned long long key)
{
    if(!resourceContainer->remove(key))
        return false;

    emit removed(key);

    return true;
}

bool IENameManager::changeKey(const unsigned long long oldKey, const unsigned long long newKey)
{
    if(!resourceContainer->changeKey(oldKey, newKey))
        return false;

    emit keyChanged(oldKey, newKey);

    return true;
}

bool IENameManager::doesExist(const unsigned long long key) const
{
    return resourceContainer->doesExist(key);
}

bool IENameManager::doesExist(const QString* value) const
{
    return resourceContainer->doesExist(value);
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

const QString* IENameManager::getValue(const unsigned long long key) const
{
    return resourceContainer->getValue(key);
}

IEResourceContainer<QString>* IENameManager::getResourceContainer() const
{
    return resourceContainer;
}

void IENameManager::setResourceContainer(IEResourceContainer<QString>* val)
{
    resourceContainer = val;
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







