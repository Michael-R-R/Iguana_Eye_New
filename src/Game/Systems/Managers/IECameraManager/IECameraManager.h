#pragma once

#include "IEResourceManager.h"

class IECameraManager : public IEResourceManager
{

public:
    IECameraManager(QObject* parent = nullptr);
    virtual ~IECameraManager();

public:
    QDataStream& serialize(QDataStream &out, const Serializable &obj) const override;
    QDataStream& deserialize(QDataStream &in, Serializable &obj) override;
};

