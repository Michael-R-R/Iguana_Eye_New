#pragma once

#include <QDataStream>
#include <QVector>
#include <QMap>

#include "IEECSSystem.h"

class ECSOnUpdateEvent;

class IEECSRenderableSystem : public IEECSSystem
{
    struct Data
    {
        QVector<IEEntity> entityList;
        QVector<unsigned long long> renderableIdList;
        QVector<int> shownInstanceIndexList;
        QVector<int> hiddenInstanceIndexList;
        QVector<bool> isRenderableList;

        friend QDataStream& operator<<(QDataStream& out, const Data& data)
        {
            out << data.entityList << data.renderableIdList
                << data.shownInstanceIndexList << data.hiddenInstanceIndexList
                << data.isRenderableList;
            return out;
        }

        friend QDataStream& operator>>(QDataStream& in, Data& data)
        {
            in >> data.entityList >> data.renderableIdList
               >> data.shownInstanceIndexList >> data.hiddenInstanceIndexList
               >> data.isRenderableList;
            return in;
        }
    };

    Data data;

    QMap<unsigned long long, QVector<IEEntity>> shownRenderableList; // Gives a list of all entities attached and shown to a given renderable
    QMap<unsigned long long, QVector<IEEntity>> hiddenRenderableList; // Gives a list of all entities attached and hidden to a given renderable

public:
    IEECSRenderableSystem();
    ~IEECSRenderableSystem();

    int attach(const IEEntity entity) override;
    bool detach(const IEEntity entity) override;
    void onUpdateFrame(ECSOnUpdateEvent* event) override;

    int shownInstanceCount(const unsigned long long id) const;
    int hiddenInstanceCount(const unsigned long long id) const;
    QVector<unsigned long long> massReplaceRenderableId(const unsigned long long oldId, const unsigned long long newId);
    QVector<unsigned long long> massPurgeRenderableId(const unsigned long long idToPurge);

    unsigned long long getRenderableId(const int index) const;
    int getShownInstanceIndex(const int index) const;
    int getHiddenInstanceIndex(const int index) const;
    bool getIsRenderable(const int index) const;

    void setRenderableId(const int index, const unsigned long long val);
    void setShownInstanceIndex(const int index, const int val);
    void setHiddenInstanceIndex(const int index, const int val);
    void setIsRenderable(const int index, const bool val);

    friend QDataStream& operator<<(QDataStream& out, const IEECSRenderableSystem& system)
    {
        out << system.entityMap << system.data
            << system.shownRenderableList << system.hiddenRenderableList;
        return out;
    }

    friend QDataStream& operator>>(QDataStream& in, IEECSRenderableSystem& system)
    {
        in >> system.entityMap >> system.data
           >> system.shownRenderableList >> system.hiddenRenderableList;
        return in;
    }
};

