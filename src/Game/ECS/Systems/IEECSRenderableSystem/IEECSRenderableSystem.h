#pragma once

#include <QDataStream>
#include <QVector>
#include <QMap>
#include <QVector2D>
#include <QVector3D>
#include <QVector4D>
#include <QMatrix4x4>

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
        QVector<int> shownInstanceIndexList;
        QVector<int> hiddenInstanceIndexList;
        QVector<QMap<QString, QVector2D>> tempVec2Data;

        friend QDataStream& operator<<(QDataStream& out, const Data& data)
        {
            out << data.entityList
                << data.renderableIdList
                << data.shownInstanceIndexList
                << data.hiddenInstanceIndexList;

            return out;
        }

        friend QDataStream& operator>>(QDataStream& in, Data& data)
        {
            in >> data.entityList
               >> data.renderableIdList
               >> data.shownInstanceIndexList
               >> data.hiddenInstanceIndexList;

            return in;
        }
    };

    Data data;

    // DOES NOT OWN THIS POINTER
    IERenderableManager* renderableManager;

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
    int getShownInstanceIndex(const int index) const;
    int getHiddenInstanceIndex(const int index) const;
    QMap<QString, QVector2D> getTempVec2Data(const int index) const;

    void setRenderableId(const int index, const unsigned long long val);
    void setShownInstanceIndex(const int index, const int val);
    void setHiddenInstanceIndex(const int index, const int val);
    void setTempVec2Data(const int index, const QMap<QString, QVector2D>& val);

private:
    void removeInstanceFromRenderable(const unsigned long long id, const IEEntity& entity);

public:
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

