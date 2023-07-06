#pragma once

#include <QDataStream>

#include "IEECSResourceSystem.h"

class IEGame;
class IEMaterial;
class IEMaterialManager;

class IEECSMaterialSystem : public IEECSResourceSystem
{
    IEMaterialManager* materialManager;

public:
    IEECSMaterialSystem(QObject* parent = nullptr);
    ~IEECSMaterialSystem();

    void startUp(const IEGame& game);
    void shutdown(const IEGame& game) override;
    IEMaterial* getAttachedResource(const int index);

    QDataStream& serialize(QDataStream &out, const IESerializable &obj) const override;
    QDataStream& deserialize(QDataStream &in, IESerializable &obj) override;
};

