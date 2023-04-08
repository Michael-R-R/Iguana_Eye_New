#pragma once

#include <QDataStream>
#include <QVector>

#include "IEECSSystem.h"

class ECSOnUpdateEvent;
class IEMesh;

class IEECSMeshSystem : public IEECSSystem
{
    struct Data
    {
        QVector<IEEntity> entity;
        QVector<unsigned long long> meshId;

        friend QDataStream& operator<<(QDataStream& out, const Data& data)
        {
            out << data.entity << data.meshId;
            return out;
        }

        friend QDataStream& operator>>(QDataStream& in, Data& data)
        {
            in >> data.entity >> data.meshId;
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

    QVector<unsigned long long> massReplaceMeshId(const unsigned long long oldId, const unsigned long long newId);
    QVector<unsigned long long> massPurgeMeshId(const unsigned long long idToPurge);
    QSharedPointer<IEMesh> getAttachedMesh(const int index);

    unsigned long long getMeshId(const int index);
    void setMeshId(const int index, const unsigned long long val);

    QDataStream& serialize(QDataStream &out, const Serializable &obj) const override;
    QDataStream& deserialize(QDataStream &in, Serializable &obj) override;
};

