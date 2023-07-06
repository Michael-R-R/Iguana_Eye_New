#pragma once

#include "IEResource.h"

class IEFileResource : public IEResource
{

public:
    IEFileResource(QObject* parent = nullptr);
    IEFileResource(const QString& path, QObject* parent = nullptr);
    IEFileResource(const IEFileResource&) = delete;
    virtual ~IEFileResource();

    bool operator==(const IEFileResource& other) { return IEResource::operator==(other); }
    bool operator!=(const IEFileResource& other) { return IEResource::operator!=(other); }
    bool operator<(const IEFileResource& other) { return IEResource::operator<(other); }
    bool operator>(const IEFileResource& other) { return IEResource::operator>(other); }

    uint64_t updateId(const QString& path) override;

    QDataStream& serialize(QDataStream& out, const IESerializable& obj) const override;
    QDataStream& deserialize(QDataStream& in, IESerializable& obj) override;
};

