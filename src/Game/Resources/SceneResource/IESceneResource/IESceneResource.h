#pragma once

#include "IEResource.h"

class IESceneResource : public IEResource
{

public:
    IESceneResource(QObject* parent = nullptr);
    IESceneResource(const QString& path, QObject* parent = nullptr);
    IESceneResource(const IESceneResource&) = delete;
    virtual ~IESceneResource();

    uint64_t updateId(const QString& path) override;

    QDataStream& serialize(QDataStream& out, const IESerializable& obj) const override;
    QDataStream& deserialize(QDataStream& in, IESerializable& obj) override;
};

