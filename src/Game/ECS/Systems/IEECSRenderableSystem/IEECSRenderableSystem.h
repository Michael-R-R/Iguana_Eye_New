#pragma once

#include <QDataStream>
#include <QVector>
#include <QMap>

#include "IEECSSystem.h"

class GameStartEvent;
class ECSOnUpdateEvent;
class IERenderableManager;

class IEECSRenderableSystem : public IEECSSystem
{
    struct Data
    {
        QVector<IEEntity> entityList;
        QVector<unsigned long long> renderableIdList;
        QVector<int> instanceIndexList;

        friend QDataStream& operator<<(QDataStream& out, const Data& data)
        {
            out << data.entityList << data.renderableIdList << data.instanceIndexList;
            return out;
        }

        friend QDataStream& operator>>(QDataStream& in, Data& data)
        {
            in >> data.entityList >> data.renderableIdList >> data.instanceIndexList;
            return in;
        }
    };

    Data data;

public:
    IEECSRenderableSystem();
    ~IEECSRenderableSystem();

    void startup(const GameStartEvent& event) override;
    int attach(const IEEntity entity) override;
    bool detach(const IEEntity entity) override;
    void onUpdateFrame(ECSOnUpdateEvent* event) override;

    QVector<unsigned long long> massReplaceRenderableId(const unsigned long long oldId, const unsigned long long newId);
    QVector<unsigned long long> massPurgeRenderableId(const unsigned long long idToPurge);

    unsigned long long getRenderableId(const int index) const;
    int getInstanceIndex(const int index) const;

    void setRenderableId(const int index, const unsigned long long val);
    void setInstanceIndex(const int index, const int val);

    friend QDataStream& operator<<(QDataStream& out, const IEECSRenderableSystem& system)
    {
        out << system.entityMap << system.data;
        return out;
    }

    friend QDataStream& operator>>(QDataStream& in, IEECSRenderableSystem& system)
    {
        in >> system.entityMap >> system.data;
        return in;
    }
};

