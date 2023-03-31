#pragma once

#include <QObject>

class IEObject : public QObject
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

signals:
    void message(const QString& msg, const IEObject::MessageType type = IEObject::MessageType::Normal);
};

