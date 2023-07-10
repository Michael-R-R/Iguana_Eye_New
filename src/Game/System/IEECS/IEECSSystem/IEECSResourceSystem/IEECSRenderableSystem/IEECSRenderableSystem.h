#pragma once

#include <QDataStream>
#include <QVector>
#include <QHash>

#include "IEECSResourceSystem.h"

class IEInstRenderable;
class IERenderableManager;

class IEECSRenderableSystem : public IEECSResourceSystem
{
    struct MoreData
    {
        QVector<int> shownIndex;
        QVector<int> hiddenIndex;

        friend QDataStream& operator<<(QDataStream& out, const MoreData& data)
        {
            out << data.shownIndex << data.hiddenIndex;
            return out;
        }

        friend QDataStream& operator>>(QDataStream& in, MoreData& data)
        {
            in >> data.shownIndex >> data.hiddenIndex;
            return in;
        }
    };

    MoreData moreData;
    QHash<uint64_t, QHash<int, IEEntity>> ShownMappedIndices;
    QHash<uint64_t, QHash<int, IEEntity>> HiddenMappedIndices;

    IERenderableManager* renderableManager;

public:
    IEECSRenderableSystem(QObject* parent = nullptr);
    ~IEECSRenderableSystem();

    int attach(const IEEntity entity) override;
    bool detach(const IEEntity entity) override;
    void startUp(const IEGame& game) override;
    void shutdown(const IEGame& game) override;
    QSet<int> massReplaceResourceId(const uint64_t oldId, const uint64_t newId) override;

    IEInstRenderable* getAttachedResource(const int index);
    int getShownIndex(const int index) const;
    int getHiddenIndex(const int index) const;

    int addShown(const int index);
    bool removeShown(const int index);
    int addHidden(const int index);
    bool removeHidden(const int index);
    void removeInstance(const int index);

private:
    int createInstance(const int index);
    int hiddenToShown(const int index);
    bool doesMappedIdExist(const uint64_t id, const QHash<uint64_t, QHash<int, IEEntity>>& map);
    bool doesMappedIndexExist(const uint64_t id, const int index, const QHash<uint64_t, QHash<int, IEEntity>>& map);
    void updateSwappedIndex(const uint64_t id, const int lastIndex, const int newIndex, QVector<int>& list, QHash<uint64_t, QHash<int, IEEntity>>& map);
    void addMappedIndex(const uint64_t id, const int index, const IEEntity& entity, QHash<uint64_t, QHash<int, IEEntity>>& map);
    void replaceMappedIndex(const uint64_t id, const int oldIndex, const int newIndex, QHash<uint64_t, QHash<int, IEEntity>>& map);
    void removeMappedIndex(const uint64_t id, const int index, QHash<uint64_t, QHash<int, IEEntity>>& map);

public:
    QDataStream& serialize(QDataStream &out, const IESerializable &obj) const override;
    QDataStream& deserialize(QDataStream &in, IESerializable &obj) override;
};

