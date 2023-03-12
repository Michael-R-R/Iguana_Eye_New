#pragma once

#include "IEBuffer.h"
#include "Serializable.h"

class IEIndexBuffer : public IEBuffer<unsigned>, public Serializable
{

public:
    IEIndexBuffer();
    IEIndexBuffer(const QVector<unsigned>& data_);
    IEIndexBuffer(const IEIndexBuffer& other);

    ~IEIndexBuffer() {}

    void build(const int = -1) override;

    QDataStream& serialize(QDataStream &out, const Serializable &obj) const override;
    QDataStream& deserialize(QDataStream &in, Serializable &obj) override;
};

