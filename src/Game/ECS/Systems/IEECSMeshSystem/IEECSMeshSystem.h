#pragma once

#include <QDataStream>
#include <QVector>

#include "IEECSSystem.h"

class GameStartEvent;
class ECSOnUpdateEvent;
class IEMeshManager;
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

    // DOES NOT OWN THIS POINTER
    IEMeshManager* meshManager;

public:
    IEECSMeshSystem();
    ~IEECSMeshSystem();

    void startup(const GameStartEvent& event) override;
    int attach(const IEEntity entity) override;
    bool detach(const IEEntity entity) override;
    void onUpdateFrame(ECSOnUpdateEvent* event) override;

    QVector<unsigned long long> massReplaceMeshId(const unsigned long long oldId, const unsigned long long newId);
    QVector<unsigned long long> massPurgeMeshId(const unsigned long long idToPurge);
    IEMesh* getAttachedMesh(const int index);

    unsigned long long getMeshId(const int index);
    void setMeshId(const int index, const unsigned long long val);

    QDataStream& serialize(QDataStream &out, const Serializable &obj) const override;
    QDataStream& deserialize(QDataStream &in, Serializable &obj) override;
};

