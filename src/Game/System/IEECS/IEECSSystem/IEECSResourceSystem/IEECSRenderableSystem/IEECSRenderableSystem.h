#pragma once

#include <QDataStream>
#include <QVector>

#include "IEECSResourceSystem.h"

class IERenderable;
class IERenderableManager;

class IEECSRenderableSystem : public IEECSResourceSystem
{
    struct MoreData
    {
        friend QDataStream& operator<<(QDataStream& out, const MoreData& data)
        {
            return out;
        }

        friend QDataStream& operator>>(QDataStream& in, MoreData& data)
        {
            return in;
        }
    };

    MoreData moreData;

    IERenderableManager* renderableManager;

public:
    IEECSRenderableSystem(QObject* parent = nullptr);
    ~IEECSRenderableSystem();

    int attach(const IEEntity entity) override;
    bool detach(const IEEntity entity) override;
    void startUp(const IEGame& game) override;
    void shutdown(const IEGame& game) override;

    IERenderable* getAttachedResource(const int index);

public:
    QDataStream& serialize(QDataStream &out, const IESerializable &obj) const override;
    QDataStream& deserialize(QDataStream &in, IESerializable &obj) override;
};

