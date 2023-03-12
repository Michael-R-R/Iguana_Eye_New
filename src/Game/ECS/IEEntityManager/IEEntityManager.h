#pragma once

#include <QMap>
#include <QStack>

#include "IEEntity.h"
#include "Serializable.h"

class IEEntityManager : public Serializable
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
    int count() const;

    QDataStream& serialize(QDataStream& out, const Serializable& obj) const override;
    QDataStream& deserialize(QDataStream& in, Serializable& obj) override;
};
