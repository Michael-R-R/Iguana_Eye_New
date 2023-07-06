#pragma once

#include <QDataStream>

#include "IEECSResourceSystem.h"

class IEGame;
class IEMesh;
class IEMeshManager;

class IEECSMeshSystem : public IEECSResourceSystem
{
    IEMeshManager* meshManager;

public:
    IEECSMeshSystem(QObject* parent = nullptr);
    ~IEECSMeshSystem();

    void startUp(const IEGame& game) override;
    void shutdown(const IEGame& game) override;
    IEMesh* getAttachedResource(const int index);

    QDataStream& serialize(QDataStream &out, const IESerializable &obj) const override;
    QDataStream& deserialize(QDataStream &in, IESerializable &obj) override;
};

