#pragma once

#include "IEResource.h"

class IESceneResource : public IEResource
{

public:
    IESceneResource(QObject* parent = nullptr);
    IESceneResource(const QString& path, QObject* parent = nullptr);
    IESceneResource(const IESceneResource&) = delete;
    virtual ~IESceneResource();

    unsigned long long updateId(const QString& path) override;

    QDataStream& serialize(QDataStream& out, const Serializable& obj) const override;
    QDataStream& deserialize(QDataStream& in, Serializable& obj) override;
};

