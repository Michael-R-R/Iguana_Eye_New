#pragma once

#include "IEResourceManager.h"

class IEShaderManager : public IEResourceManager
{
    uint64_t defaultID;

public:
    IEShaderManager(QObject* parent = nullptr);
    ~IEShaderManager();

    void startup(IEGame& game) override;

    uint64_t getDefaultID() const { return defaultID; }

    QDataStream& serialize(QDataStream &out, const IESerializable &obj) const override;
    QDataStream& deserialize(QDataStream &in, IESerializable &obj) override;
};
