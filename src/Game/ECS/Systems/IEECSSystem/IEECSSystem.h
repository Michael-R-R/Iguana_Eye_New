#pragma once

#include <QDataStream>
#include <QMap>

#include "IEEntity.h"

class GameStartEvent;
class ECSOnUpdateEvent;

class IEECSSystem
{
protected:
    QMap<IEEntity, int> entityMap; // Entity, index

public:
    IEECSSystem();
    ~IEECSSystem();

    virtual void startup(const GameStartEvent& event) = 0;
    virtual int attach(const IEEntity entity) = 0;
    virtual bool detach(const IEEntity entity) = 0;
    virtual void onUpdateFrame(ECSOnUpdateEvent* event) = 0;

    bool doesExist(const IEEntity& key) const;
    int lookUpIndex(const IEEntity& key) const;
    bool indexBoundCheck(const int index) const;
};
