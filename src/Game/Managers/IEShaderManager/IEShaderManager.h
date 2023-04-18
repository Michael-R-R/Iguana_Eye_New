#pragma once

#include "IEResourceManager.h"

class IEShaderManager : public IEResourceManager
{

public:
    IEShaderManager(QObject* parent = nullptr);
    ~IEShaderManager();

    void startup() override;

public:
    QDataStream& serialize(QDataStream &out, const Serializable &obj) const override;
    QDataStream& deserialize(QDataStream &in, Serializable &obj) override;
};
