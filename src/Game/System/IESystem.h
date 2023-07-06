#pragma once

#include "IEObject.h"

class IEGame;

class IESystem : public IEObject
{
    Q_OBJECT

public:
    IESystem(QObject* parent = nullptr) : IEObject(parent) {}
    virtual ~IESystem() {}

    virtual void startup(IEGame&) { }
    virtual void shutdown(IEGame&) { }
    virtual void onSerialize(IEGame&) { }
    virtual void onDeserialize(IEGame&) { }
    virtual void onUpdateFrame() { }

    QDataStream& serialize(QDataStream& out, const IESerializable& obj) const override;
    QDataStream& deserialize(QDataStream& in, IESerializable& obj) override;
};

