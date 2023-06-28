#pragma once

#include "IEResourceManager.h"

class IEMeshManager : public IEResourceManager
{

public:
    IEMeshManager(QObject* parent = nullptr);
    ~IEMeshManager();

public:
    QDataStream& serialize(QDataStream &out, const Serializable &obj) const override;
    QDataStream& deserialize(QDataStream &in, Serializable &obj) override;
};
