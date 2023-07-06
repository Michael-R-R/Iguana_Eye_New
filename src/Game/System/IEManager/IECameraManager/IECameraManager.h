#pragma once

#include "IEResourceManager.h"

class IECameraManager : public IEResourceManager
{

public:
    IECameraManager(QObject* parent = nullptr);
    virtual ~IECameraManager();

public:
    QDataStream& serialize(QDataStream &out, const IESerializable &obj) const override;
    QDataStream& deserialize(QDataStream &in, IESerializable &obj) override;
};

