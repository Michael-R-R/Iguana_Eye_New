#pragma once

#include "IEResourceManager.h"

class IEMeshManager : public IEResourceManager
{

public:
    IEMeshManager(QObject* parent = nullptr);
    virtual ~IEMeshManager();

public:
    QDataStream& serialize(QDataStream &out, const IESerializable &obj) const override;
    QDataStream& deserialize(QDataStream &in, IESerializable &obj) override;
};
