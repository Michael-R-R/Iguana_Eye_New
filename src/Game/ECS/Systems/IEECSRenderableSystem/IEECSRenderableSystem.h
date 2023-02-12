#pragma once

#include <QDataStream>
#include <QVector>

#include "IEECSSystem.h"

class ECSOnUpdateEvent;

class IEECSRenderableSystem : public IEECSSystem
{
    struct Data
    {
        QVector<IEEntity> entityList;
        QVector<unsigned long long> renderableIdList;
        QVector<bool> isRenderableList;

        friend QDataStream& operator<<(QDataStream& out, const Data& data)
        {
            out << data.entityList << data.renderableIdList << data.isRenderableList;
            return out;
        }

        friend QDataStream& operator>>(QDataStream& in, Data& data)
        {
            in >> data.entityList >> data.renderableIdList >> data.isRenderableList;
            return in;
        }
    };

    Data data;

public:
    IEECSRenderableSystem();
    ~IEECSRenderableSystem();

    int attach(const IEEntity entity) override;
    bool detach(const IEEntity entity) override;
    void onUpdateFrame(ECSOnUpdateEvent* event) override;

    QVector<unsigned long long> massReplaceRenderableId(const unsigned long long oldId, const unsigned long long newId);
    QVector<unsigned long long> massPurgeRenderableId(const unsigned long long idToPurge);

    unsigned long long getRenderableId(const int index);
    bool getIsRenderable(const int index);

    void setRenderableId(const int index, const unsigned long long val);
    void setIsRenderable(const int index, const bool val);

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

