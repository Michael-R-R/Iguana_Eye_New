#pragma once

#include <QMap>
#include <QString>

#include "IEObject.h"
#include "IEEntity.h"

class IEGame;
class ECSOnUpdateEvent;

class IEECSSystem : public IEObject
{
protected:
    QMap<IEEntity, int> entityMap; // Entity, index

public:
    IEECSSystem(QObject* parent = nullptr);
    virtual ~IEECSSystem();

    virtual int attach(const IEEntity entity) = 0;
    virtual bool detach(const IEEntity entity) = 0;

    virtual void startUp(const IEGame&) { }
    virtual void onSerialize(const IEGame&) { }
    virtual void onDeserialize(const IEGame&) { }
    virtual void onUpdateFrame() { }

    QDataStream& serialize(QDataStream& out, const Serializable& obj) const override;
    QDataStream& deserialize(QDataStream& in, Serializable& obj) override;

    bool doesExist(const IEEntity& key) const;
    int lookUpIndex(const IEEntity& key) const;
    bool indexBoundCheck(const int index) const;
};
