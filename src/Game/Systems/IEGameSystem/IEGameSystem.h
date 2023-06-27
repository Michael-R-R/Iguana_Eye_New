#pragma once

#include "IEObject.h"

class IEGame;

class IEGameSystem : public IEObject
{
    Q_OBJECT

public:
    IEGameSystem(QObject* parent = nullptr) : IEObject(parent) {}
    virtual ~IEGameSystem() {}

    virtual void startup(IEGame& game) = 0;
    virtual void shutdown(IEGame& game) = 0;
    virtual void onSerialize(IEGame& game) = 0;
    virtual void onDeserialize(IEGame& game) = 0;

    virtual void onUpdateFrame() { }

    QDataStream& serialize(QDataStream& out, const Serializable& obj) const override;
    QDataStream& deserialize(QDataStream& in, Serializable& obj) override;
};

