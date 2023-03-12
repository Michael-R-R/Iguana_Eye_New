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
class IERenderable;

class IEECSRenderableSystem : public IEECSSystem
{
    struct Data
    {
        QVector<IEEntity> entity;
        QVector<unsigned long long> renderableId;
        QVector<int> shownInstanceIndex;
        QVector<int> hiddenInstanceIndex;
        QVector<QMap<QString, QVector2D>> tempVec2Data;
        QVector<QMap<QString, QVector3D>> tempVec3Data;
        QVector<QMap<QString, QVector4D>> tempVec4Data;
        QVector<QMap<QString, QMatrix4x4>> tempMat4Data;

        friend QDataStream& operator<<(QDataStream& out, const Data& data)
        {
            out << data.entity
                << data.renderableId
                << data.shownInstanceIndex
                << data.hiddenInstanceIndex;

            return out;
        }

        friend QDataStream& operator>>(QDataStream& in, Data& data)
        {
            in >> data.entity
               >> data.renderableId
               >> data.shownInstanceIndex
               >> data.hiddenInstanceIndex;

            return in;
        }
    };

    Data data;

    QMap<unsigned long long, QMap<IEEntity, int>> shownEntityMap;
    QMap<unsigned long long, QVector<IEEntity>> shownEntityList;

    QMap<unsigned long long, QMap<IEEntity, int>> hiddenEntityMap;
    QMap<unsigned long long, QVector<IEEntity>> hiddenEntityList;

    // DOES NOT OWN THIS POINTER
    IERenderableManager* renderableManager;

public:
    IEECSRenderableSystem();
    ~IEECSRenderableSystem();

    void startup(const GameStartEvent& event) override;
    int attach(const IEEntity entity) override;
    bool detach(const IEEntity entity) override;
    void onUpdateFrame(ECSOnUpdateEvent* event) override;

    void addShown(const int index);
    void addHidden(const int index);
    void removeShown(const int index);
    void removeHidden(const int index);
    bool doesExistShown(const int index) const;
    bool doesExistHidden(const int index) const;
    void transferTempData(const int index);

    QVector<unsigned long long> massReplaceRenderableId(const unsigned long long oldId, const unsigned long long newId);
    QVector<unsigned long long> massPurgeRenderableId(const unsigned long long idToPurge);
    IERenderable* getAttachedRenderable(const int index) const;

    unsigned long long getRenderableId(const int index) const;
    int getShownInstanceIndex(const int index) const;
    int getHiddenInstanceIndex(const int index) const;

    void setRenderableId(const int index, const unsigned long long val);
    void setShownInstanceIndex(const int index, const int val);
    void setHiddenInstanceIndex(const int index, const int val);

private:
    int add(const IEEntity& entity, QMap<IEEntity, int>& map, QVector<IEEntity>& list);
    std::tuple<IEEntity, int> remove(const IEEntity& entity, QMap<IEEntity, int>& map, QVector<IEEntity>& list);
    void removeInstanceFromRenderable(const int index);
    void cacheTempData(const int index);
    void clearTempData(const int index);

public:
    QDataStream& serialize(QDataStream &out, const Serializable &obj) const override;
    QDataStream& deserialize(QDataStream &in, Serializable &obj) override;
};

