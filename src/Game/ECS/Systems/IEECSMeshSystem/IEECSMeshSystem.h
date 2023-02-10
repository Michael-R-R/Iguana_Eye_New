#pragma once

#include <QDataStream>

#include "IEECSSystem.h"

class ECSOnUpdateEvent;

class IEECSMeshSystem : public IEECSSystem
{
    struct Data
    {
        friend QDataStream& operator<<(QDataStream& out, const Data& data)
        {
            return out;
        }

        friend QDataStream& operator>>(QDataStream& in, Data& data)
        {
            return in;
        }
    };

    Data data;

public:
    IEECSMeshSystem();
    ~IEECSMeshSystem();

    int attach(const IEEntity entity) override;
    bool detach(const IEEntity entity) override;
    void onUpdateFrame(ECSOnUpdateEvent* event) override;
    void onPostUpdateFrame() override;
    void onRenderFrame() override;

    friend QDataStream& operator<<(QDataStream& out, const IEECSMeshSystem& system)
    {
        out << system.entityMap << system.data;
        return out;
    }

    friend QDataStream& operator>>(QDataStream& in, IEECSMeshSystem& system)
    {
        in >> system.entityMap >> system.data;
        return in;
    }
};

