#pragma once

#include "IEResourceManager.h"

class IEMaterialManager: public IEResourceManager
{

public:
    IEMaterialManager(QObject* parent = nullptr);
    ~IEMaterialManager();

    void startup(IEGame&) override;

public:
    QDataStream& serialize(QDataStream &out, const Serializable &obj) const override;
    QDataStream& deserialize(QDataStream &in, Serializable &obj) override;
};
