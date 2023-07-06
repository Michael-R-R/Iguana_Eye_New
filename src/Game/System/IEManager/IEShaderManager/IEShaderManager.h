#pragma once

#include "IEResourceManager.h"

class IEShaderManager : public IEResourceManager
{

public:
    IEShaderManager(QObject* parent = nullptr);
    ~IEShaderManager();

    void startup(IEGame&) override;

public:
    QDataStream& serialize(QDataStream &out, const IESerializable &obj) const override;
    QDataStream& deserialize(QDataStream &in, IESerializable &obj) override;
};
