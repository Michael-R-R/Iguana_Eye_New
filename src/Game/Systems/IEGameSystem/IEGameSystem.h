#pragma once

#include "Serializable.h"

class IEGameSystem : public Serializable
{
public:
    virtual ~IEGameSystem() {};

    virtual void startup() = 0;
    virtual void shutdown() = 0;
    virtual void reset() = 0;

    QDataStream& serialize(QDataStream& out, const Serializable& obj) const override;
    QDataStream& deserialize(QDataStream& in, Serializable& obj) override;
};

