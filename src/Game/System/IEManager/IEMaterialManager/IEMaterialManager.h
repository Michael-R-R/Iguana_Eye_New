#pragma once

#include "IEResourceManager.h"

class IEMaterialManager: public IEResourceManager
{

public:
    IEMaterialManager(QObject* parent = nullptr);
    virtual ~IEMaterialManager();

public:
    QDataStream& serialize(QDataStream &out, const IESerializable &obj) const override;
    QDataStream& deserialize(QDataStream &in, IESerializable &obj) override;
};
