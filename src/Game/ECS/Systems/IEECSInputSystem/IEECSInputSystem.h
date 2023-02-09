#pragma once

#include <QDataStream>
#include <QVector>

#include "IEECSSystem.h"

struct InputDataECS
{
    QVector<IEEntity> entityList;
    QVector<bool> hasInputList;

    friend QDataStream& operator<<(QDataStream& out, const InputDataECS& data)
    {
        out << data.entityList << data.hasInputList;
        return out;
    }

    friend QDataStream& operator>>(QDataStream& in, InputDataECS& data)
    {
        in >> data.entityList >> data.hasInputList;
        return in;
    }
};

class IEECSInputSystem : public IEECSSystem
{
    InputDataECS data;

public:
    IEECSInputSystem();
    ~IEECSInputSystem();

    int attach(const IEEntity entity) override;
    bool detach(const IEEntity entity) override;
    void onUpdateFrame() override;
    void onPostUpdateFrame() override;
    void onRenderFrame() override;

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
