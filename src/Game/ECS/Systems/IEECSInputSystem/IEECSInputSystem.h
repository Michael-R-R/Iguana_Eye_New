#pragma once

#include <QVector>

#include "IEECSSystem.h"

class ECSOnUpdateEvent;

class IEECSInputSystem : public IEECSSystem
{
    struct Data
    {
        QVector<IEEntity> entity;
        QVector<bool> hasInput;

        friend QDataStream& operator<<(QDataStream& out, const Data& data)
        {
            out << data.entity << data.hasInput;
            return out;
        }

        friend QDataStream& operator>>(QDataStream& in, Data& data)
        {
            in >> data.entity >> data.hasInput;
            return in;
        }
    };

    Data data;

public:
    IEECSInputSystem(QObject* parent = nullptr);
    ~IEECSInputSystem();

    int attach(const IEEntity entity) override;
    bool detach(const IEEntity entity) override;
    void onUpdateFrame(ECSOnUpdateEvent& event) override;

    bool getHasInput(const int index) const;
    void setHasInput(const int index, const bool val);

    QDataStream& serialize(QDataStream &out, const Serializable &obj) const override;
    QDataStream& deserialize(QDataStream &in, Serializable &obj) override;
};
