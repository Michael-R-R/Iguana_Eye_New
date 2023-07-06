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
    size_t id; // id comes from dervied type hash code
    QMap<IEEntity, int> entityMap; // Entity, index

public:
    IEECSSystem(size_t _id, QObject* parent = nullptr);
    virtual ~IEECSSystem();

    virtual int attach(const IEEntity entity) = 0;
    virtual bool detach(const IEEntity entity) = 0;

    virtual void startUp(const IEGame&) { }
    virtual void shutdown(const IEGame&) { }
    virtual void onSerialize(const IEGame&) { }
    virtual void onDeserialize(const IEGame&) { }
    virtual void onUpdateFrame() { }

    QDataStream& serialize(QDataStream& out, const IESerializable& obj) const override;
    QDataStream& deserialize(QDataStream& in, IESerializable& obj) override;

    bool doesExist(const IEEntity& key) const;
    int lookUpIndex(const IEEntity& key) const;
    bool indexBoundCheck(const int index) const;

    size_t getID() { return id; }
};
