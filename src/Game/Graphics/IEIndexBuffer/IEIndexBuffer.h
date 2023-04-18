#pragma once

#include "IEBuffer.h"

class IEIndexBuffer : public IEBuffer<unsigned>
{

public:
    IEIndexBuffer(QObject* parent = nullptr);
    IEIndexBuffer(const QVector<unsigned>& data_, QObject* parent = nullptr);
    IEIndexBuffer(const IEIndexBuffer&) = delete;
    ~IEIndexBuffer();

    void build(const int = -1) override;

    QDataStream& serialize(QDataStream &out, const Serializable &obj) const override;
    QDataStream& deserialize(QDataStream &in, Serializable &obj) override;
};

