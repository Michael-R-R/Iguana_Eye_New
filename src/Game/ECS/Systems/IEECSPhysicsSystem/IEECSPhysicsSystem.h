#pragma once

#include <QVector>
#include <QMap>
#include <vector>

#include "IEECSSystem.h"

class IEECSPhysicsSystem : public IEECSSystem
{
    struct Data
    {
        QVector<IEEntity> entity;

        friend QDataStream& operator<<(QDataStream& out, const Data& data)
        {
            out << data.entity;
            return out;
        }

        friend QDataStream& operator>>(QDataStream& in, Data& data)
        {
            in >> data.entity;
            return in;
        }
    };

    Data data;

public:
    IEECSPhysicsSystem();
    ~IEECSPhysicsSystem();

    void startup(const GameStartEvent& event) override;
    int attach(const IEEntity entity) override;
    bool detach(const IEEntity entity) override;
    void onUpdateFrame(ECSOnUpdateEvent* event) override;

    QDataStream& serialize(QDataStream& out, const Serializable& obj) const override;
    QDataStream& deserialize(QDataStream& in, Serializable& obj) override;
};

