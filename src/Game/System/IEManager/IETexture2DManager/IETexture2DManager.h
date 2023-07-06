#pragma once

#include "IEResourceManager.h"

class IETexture2DManager : public IEResourceManager
{
public:
    IETexture2DManager(QObject* parent = nullptr);
    virtual ~IETexture2DManager();

    QDataStream& serialize(QDataStream& out, const IESerializable& obj) const override;
    QDataStream& deserialize(QDataStream& in, IESerializable& obj) override;
};

