#pragma once

#include <QObject>

#include "Serializable.h"

class IEObject : public QObject, public Serializable
{
    Q_OBJECT

public:
    enum class MessageType
    {
        Normal, Error
    };

public:
    IEObject(QObject* parent = nullptr);
    ~IEObject();

    QDataStream& serialize(QDataStream& out, const Serializable& obj) const override;
    QDataStream& deserialize(QDataStream& in, Serializable& obj) override;

signals:
    void message(const QString& msg, const IEObject::MessageType type = IEObject::MessageType::Normal);
};

