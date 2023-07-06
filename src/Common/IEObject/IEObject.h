#pragma once

#include <QObject>

#include "IESerializable.h"

class IEObject : public QObject, public IESerializable
{
    Q_OBJECT

public:
    enum class MessageType
    {
        Normal, Error
    };

public:
    IEObject(QObject* parent = nullptr);
    virtual ~IEObject();

    QDataStream& serialize(QDataStream& out, const IESerializable& obj) const override;
    QDataStream& deserialize(QDataStream& in, IESerializable& obj) override;

signals:
    void message(const QString& msg, const IEObject::MessageType type = IEObject::MessageType::Normal);
};

