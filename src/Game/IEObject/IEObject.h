#pragma once

#include <QObject>

class IEObject : public QObject
{
public:
    enum class MessageType
    {
        Normal, Error
    };

private:
    Q_OBJECT

public:
    IEObject(QObject* parent = nullptr);
    ~IEObject();

signals:
    void message(const QString& msg, const IEObject::MessageType type = IEObject::MessageType::Normal);
};

