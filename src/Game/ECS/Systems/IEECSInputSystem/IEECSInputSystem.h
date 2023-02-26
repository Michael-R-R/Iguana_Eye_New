#pragma once

#include <QDataStream>
#include <QVector>

#include "IEECSSystem.h"

class GameStartEvent;
class ECSOnUpdateEvent;

class IEECSInputSystem : public IEECSSystem
{
    struct Data
    {
        QVector<IEEntity> entityList;
        QVector<bool> hasInputList;

        friend QDataStream& operator<<(QDataStream& out, const Data& data)
        {
            out << data.entityList << data.hasInputList;
            return out;
        }

        friend QDataStream& operator>>(QDataStream& in, Data& data)
        {
            in >> data.entityList >> data.hasInputList;
            return in;
        }
    };

    Data data;

public:
    IEECSInputSystem();
    ~IEECSInputSystem();

    void startup(const GameStartEvent& event) override;
    int attach(const IEEntity entity) override;
    bool detach(const IEEntity entity) override;
    void onUpdateFrame(ECSOnUpdateEvent* event) override;

    bool getHasInput(const int index) const;
    void setHasInput(const int index, const bool val);

    friend QDataStream& operator<<(QDataStream& out, const IEECSInputSystem& system)
    {
        out << system.entityMap << system.data;
        return out;
    }

    friend QDataStream& operator>>(QDataStream& in, IEECSInputSystem& system)
    {
        in >> system.entityMap >> system.data;
        return in;
    }
};
