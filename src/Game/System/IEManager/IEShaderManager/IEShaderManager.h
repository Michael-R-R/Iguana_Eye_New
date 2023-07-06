#pragma once

#include "IEResourceManager.h"

class IEShaderManager : public IEResourceManager
{

public:
    IEShaderManager(QObject* parent = nullptr);
    ~IEShaderManager();

public:
    QDataStream& serialize(QDataStream &out, const IESerializable &obj) const override;
    QDataStream& deserialize(QDataStream &in, IESerializable &obj) override;
};
