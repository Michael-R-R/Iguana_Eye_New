#pragma once

#include <QDataStream>
#include <QMap>
#include <QStack>

#include "IEEntity.h"

class IEEntityManager
{
    QMap<IEEntity, unsigned long long> entityMap; // <Entity, Attached components>
    QStack<int> freeIdStack;
    int nextId;

public:
    IEEntityManager();
    ~IEEntityManager();

    IEEntity create();
    bool remove(const IEEntity key);
    bool attachComponent(const IEEntity& key, const unsigned long long component);
    bool detachComponent(const IEEntity& key, const unsigned long long component);
    bool doesExist(const IEEntity& key) const;
    bool hasComponent(const IEEntity& key, const unsigned long long component) const;
    unsigned long long getAttachComponents(const IEEntity& key) const;

    friend QDataStream& operator<<(QDataStream& out, const IEEntityManager& manager)
    {
        out << manager.entityMap
            << manager.freeIdStack
            << manager.nextId;

        return out;
    }

    friend QDataStream& operator>>(QDataStream& in, IEEntityManager& manager)
    {
        in >> manager.entityMap
           >> manager.freeIdStack
           >> manager.nextId;

        return in;
    }
};
