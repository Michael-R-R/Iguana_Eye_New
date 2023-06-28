#pragma once

#include "IEObject.h"

class IEGame;

class IEGameSystem : public IEObject
{
    Q_OBJECT

public:
    IEGameSystem(QObject* parent = nullptr) : IEObject(parent) {}
    virtual ~IEGameSystem() {}

    virtual void startup(IEGame&) { }
    virtual void shutdown(IEGame&) { }
    virtual void onSerialize(IEGame&) { }
    virtual void onDeserialize(IEGame&) { }
    virtual void onUpdateFrame() { }

    QDataStream& serialize(QDataStream& out, const Serializable& obj) const override;
    QDataStream& deserialize(QDataStream& in, Serializable& obj) override;
};

