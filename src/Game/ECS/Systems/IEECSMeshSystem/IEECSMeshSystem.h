#pragma once

#include <QDataStream>
#include <QVector>

#include "IEECSSystem.h"

class ECSOnUpdateEvent;

class IEECSMeshSystem : public IEECSSystem
{
    struct Data
    {
        QVector<IEEntity> entityList;
        QVector<unsigned long long> meshIdList;

        friend QDataStream& operator<<(QDataStream& out, const Data& data)
        {
            out << data.entityList << data.meshIdList;
            return out;
        }

        friend QDataStream& operator>>(QDataStream& in, Data& data)
        {
            in >> data.entityList >> data.meshIdList;
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

    void massReplaceMeshId(const unsigned long long oldId, const unsigned long long newId);
    void massPurgeMeshId(const unsigned long long idToPurge);

    unsigned long long getMeshId(const int index);
    void setMeshId(const int index, const unsigned long long val);

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

