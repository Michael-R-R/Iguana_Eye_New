#pragma once

#include <QMap>
#include <QSet>
#include <QStack>

#include "IEObject.h"
#include "IEEntity.h"

class IEEntityManager : public IEObject
{
    QMap<IEEntity, QSet<size_t>> entityMap; // <Entity, Attached components>
    QStack<int> freeIdStack;
    int nextId;

public:
    IEEntityManager(QObject* parent = nullptr);
    ~IEEntityManager();

    IEEntity create();
    bool remove(const IEEntity key);
    bool attachComponent(const IEEntity& key, const size_t& component);
    bool detachComponent(const IEEntity& key, const size_t& component);
    bool doesEntityExist(const IEEntity& key) const;
    bool hasComponent(const IEEntity& key, const size_t& component) const;
    QSet<size_t> getAttachedComponents(const IEEntity& key) const;
    int count() const;

    QDataStream& serialize(QDataStream& out, const Serializable& obj) const override;
    QDataStream& deserialize(QDataStream& in, Serializable& obj) override;
};
