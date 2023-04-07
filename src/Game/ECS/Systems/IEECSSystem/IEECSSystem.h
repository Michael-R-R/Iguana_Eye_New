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
    IEECSSystem();
    ~IEECSSystem();

    virtual int attach(const IEEntity entity) = 0;
    virtual bool detach(const IEEntity entity) = 0;
    virtual void onUpdateFrame(ECSOnUpdateEvent* event) = 0;
    virtual void initalize() {}
    virtual void reset() {}
    QDataStream& serialize(QDataStream& out, const Serializable& obj) const override;
    QDataStream& deserialize(QDataStream& in, Serializable& obj) override;

    bool doesExist(const IEEntity& key) const;
    int lookUpIndex(const IEEntity& key) const;
    bool indexBoundCheck(const int index) const;
};
