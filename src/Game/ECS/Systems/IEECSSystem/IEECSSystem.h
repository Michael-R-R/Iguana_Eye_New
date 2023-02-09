#pragma once

#include <QDataStream>
#include <QMap>

#include "IEEntity.h"

class IEECSSystem
{
protected:
    QMap<IEEntity, int> entityMap; // Entity, index

public:
    IEECSSystem();
    ~IEECSSystem();

    virtual int attach(const IEEntity entity) = 0;
    virtual bool detach(const IEEntity entity) = 0;
    virtual void onUpdateFrame() = 0;
    virtual void onPostUpdateFrame() = 0;
    virtual void onRenderFrame() = 0;

    bool doesExist(const IEEntity& key);
    int lookUpIndex(const IEEntity& key);
    bool indexBoundCheck(const int index);

    const QMap<IEEntity, int>& getEntityMap() const { return entityMap; }
    void setEntityMap(const QMap<IEEntity, int>& val) { entityMap = val; }
};
