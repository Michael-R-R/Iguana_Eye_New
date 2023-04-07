#pragma once

#include "IEObject.h"

class IEGame;

class IEGameSystem : public IEObject
{
public:
    IEGameSystem(QObject* parent = nullptr) : IEObject(parent) {}
    virtual ~IEGameSystem() {}

    virtual void startup(IEGame& game) = 0;
    virtual void shutdown(IEGame& game) = 0;
    virtual void initalize(IEGame& game) = 0;
    virtual void reset(IEGame& game) = 0;

    QDataStream& serialize(QDataStream& out, const Serializable& obj) const override;
    QDataStream& deserialize(QDataStream& in, Serializable& obj) override;
};

