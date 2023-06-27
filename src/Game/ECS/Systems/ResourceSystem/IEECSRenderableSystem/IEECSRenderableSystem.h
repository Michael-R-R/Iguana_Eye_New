#pragma once

#include <QDataStream>
#include <QVector>
#include <QMap>
#include <QVector2D>
#include <QVector3D>
#include <QVector4D>
#include <QMatrix4x4>

#include "IEECSResourceSystem.h"

class IERenderable;
class IERenderableManager;

class IEECSRenderableSystem : public IEECSResourceSystem
{
    struct MoreData
    {
        QVector<int> shownInstanceIndex;
        QVector<int> hiddenInstanceIndex;
        QVector<QMap<QString, QVector2D>> tempVec2Data;
        QVector<QMap<QString, QVector3D>> tempVec3Data;
        QVector<QMap<QString, QVector4D>> tempVec4Data;
        QVector<QMap<QString, QMatrix4x4>> tempMat4Data;

        friend QDataStream& operator<<(QDataStream& out, const MoreData& data)
        {
            out << data.shownInstanceIndex
                << data.hiddenInstanceIndex;

            return out;
        }

        friend QDataStream& operator>>(QDataStream& in, MoreData& data)
        {
            in >> data.shownInstanceIndex
               >> data.hiddenInstanceIndex;

            return in;
        }
    };

    MoreData moreData;

    QMap<unsigned long long, QMap<IEEntity, int>> shownEntityMap;
    QMap<unsigned long long, QVector<IEEntity>> shownEntityList;

    QMap<unsigned long long, QMap<IEEntity, int>> hiddenEntityMap;
    QMap<unsigned long long, QVector<IEEntity>> hiddenEntityList;

    IERenderableManager* renderableManager;

public:
    IEECSRenderableSystem(QObject* parent = nullptr);
    ~IEECSRenderableSystem();

    int attach(const IEEntity entity) override;
    bool detach(const IEEntity entity) override;
    void startUp(const IEGame& game) override;

    int addShown(const int index);
    int addHidden(const int index);
    void removeShown(const int index);
    void removeHidden(const int index);
    bool doesExistShown(const int index) const;
    bool doesExistHidden(const int index) const;
    void transferTempData(const int index);

    IERenderable* getAttachedResource(const int index);

    int getShownInstanceIndex(const int index) const;
    int getHiddenInstanceIndex(const int index) const;

    void setShownInstanceIndex(const int index, const int val);
    void setHiddenInstanceIndex(const int index, const int val);

private:
    int add(const IEEntity& entity, QMap<IEEntity, int>& map, QVector<IEEntity>& list);
    std::tuple<IEEntity, int> remove(const IEEntity& entity, QMap<IEEntity, int>& map, QVector<IEEntity>& list);
    void removeInstance(const int index);
    void cacheTempData(const int index);
    void clearTempData(const int index);

public:
    QDataStream& serialize(QDataStream &out, const Serializable &obj) const override;
    QDataStream& deserialize(QDataStream &in, Serializable &obj) override;
};

