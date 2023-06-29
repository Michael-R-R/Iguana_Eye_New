#pragma once

#include <QVector2D>

#include "IEObject.h"

class IEGame;

class IEGameState : public IEObject
{

public:
    IEGameState(QObject* parent = nullptr) : IEObject(parent) {}
    virtual ~IEGameState() {}

    virtual void enter(IEGame& game) = 0;
    virtual void exit(IEGame& game) = 0;
    virtual void onUpdateFrame() = 0;
    virtual void onRenderFrame() = 0;
    virtual void onResize(const float w, const float h) = 0;
    virtual void onResize(const QVector2D& val);
    virtual void serializeTemporary(IEGame& game);
    virtual void deserializeTemporary(IEGame& game);

    QDataStream& serialize(QDataStream& out, const Serializable& obj) const override;
    QDataStream& deserialize(QDataStream& in, Serializable& obj) override;
};

