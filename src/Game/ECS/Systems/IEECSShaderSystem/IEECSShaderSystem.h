#pragma once

#include <QDataStream>
#include <QVector>

#include "IEECSSystem.h"

class ECSOnUpdateEvent;

class IEECSShaderSystem : public IEECSSystem
{
    struct Data
    {
        QVector<IEEntity> entityList;
        QVector<unsigned long long> shaderIdList;

        friend QDataStream& operator<<(QDataStream& out, const Data& data)
        {
            out << data.entityList << data.shaderIdList;
            return out;
        }

        friend QDataStream& operator>>(QDataStream& in, Data& data)
        {
            in >> data.entityList >> data.shaderIdList;
            return in;
        }
    };

    Data data;

public:
    IEECSShaderSystem();
    ~IEECSShaderSystem();

    int attach(const IEEntity entity) override;
    bool detach(const IEEntity entity) override;
    void onUpdateFrame(ECSOnUpdateEvent* event) override;
    void onPostUpdateFrame() override;
    void onRenderFrame() override;

    QVector<unsigned long long> massReplaceShaderId(const unsigned long long oldId, const unsigned long long newId);
    QVector<unsigned long long> massPurgeShaderId(const unsigned long long idToPurge);

    unsigned long long getShaderId(const int index);
    void setShaderId(const int index, const unsigned long long val);

    friend QDataStream& operator<<(QDataStream& out, const IEECSShaderSystem& system)
    {
        out << system.entityMap << system.data;
        return out;
    }

    friend QDataStream& operator>>(QDataStream& in, IEECSShaderSystem& system)
    {
        in >> system.entityMap >> system.data;
        return in;
    }
};

