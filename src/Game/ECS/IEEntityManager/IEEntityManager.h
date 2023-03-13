#pragma once

#include <QMap>
#include <QSet>
#include <QStack>
#include <QString>

#include "IEEntity.h"
#include "Serializable.h"

class IEEntityManager : public Serializable
{
    QMap<IEEntity, QSet<QString>> entityMap; // <Entity, Attached components>
    QStack<int> freeIdStack;
    int nextId;

public:
    IEEntityManager();
    ~IEEntityManager();

    IEEntity create();
    bool remove(const IEEntity key);
    bool attachComponent(const IEEntity& key, const QString& component);
    bool detachComponent(const IEEntity& key, const QString& component);
    bool doesEntityExist(const IEEntity& key) const;
    bool hasComponent(const IEEntity& key, const QString& component) const;
    QSet<QString> getAttachComponents(const IEEntity& key) const;
    int count() const;

    QDataStream& serialize(QDataStream& out, const Serializable& obj) const override;
    QDataStream& deserialize(QDataStream& in, Serializable& obj) override;
};
