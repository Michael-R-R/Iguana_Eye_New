#pragma once

#include <QDataStream>
#include <QVector>

#include "IEECSSystem.h"
#include "IEScript.h"

class GameStartEvent;
class ECSOnUpdateEvent;

class IEECSScriptSystem : public IEECSSystem
{
    struct Data
    {
        QVector<IEEntity> entity;
        QVector<QVector<IEScript>> scripts;

        friend QDataStream& operator<<(QDataStream& out, const Data& data)
        {
            out << data.entity << data.scripts;

            return out;
        }

        friend QDataStream& operator>>(QDataStream& in, Data& data)
        {
            in >> data.entity >> data.scripts;

            return in;
        }
    };

    Data data;

public:
    IEECSScriptSystem();
    ~IEECSScriptSystem() {}

    void startup(const GameStartEvent& event) override;
    int attach(const IEEntity entity) override;
    bool detach(const IEEntity entity) override;
    void onUpdateFrame(ECSOnUpdateEvent* event) override;

    friend QDataStream& operator<<(QDataStream& out, const IEECSScriptSystem& system)
    {
        out << system.entityMap << system.data;

        return out;
    }

    friend QDataStream& operator>>(QDataStream& in, IEECSScriptSystem& system)
    {
        in >> system.entityMap >> system.data;

        return in;
    }
};

