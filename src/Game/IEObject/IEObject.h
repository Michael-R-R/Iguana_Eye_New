#pragma once

#include <QObject>

class IEObject : public QObject
{
    enum class MessageType
    {
        Normal, Error
    };

    Q_OBJECT

public:
    IEObject(QObject* parent = nullptr);
    ~IEObject();

signals:
    void message(const QString& msg, const IEObject::MessageType type = IEObject::MessageType::Normal);
};

