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

    const QMap<IEEntity, unsigned long long>& getEntityMap() const { return entityMap; }
    const QStack<int>& getFreeIdStack() const { return freeIdStack; }
    int getNextId() const { return nextId; }

    void setEntityMap(const QMap<IEEntity, unsigned long long>& val) { entityMap = val; }
    void setFreeIdStack(const QStack<int>& val) { freeIdStack = val; }
    void setNextId(const int val) { nextId = val; }
};

QDataStream& operator<<(QDataStream& out, const IEEntityManager& manager);
QDataStream& operator>>(QDataStream& in, IEEntityManager& manager);
