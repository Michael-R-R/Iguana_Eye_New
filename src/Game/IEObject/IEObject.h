#pragma once

#include <QObject>

class IEObject : public QObject
{
    Q_OBJECT

public:
    IEObject(QObject* parent = nullptr);
    ~IEObject();

signals:
    void message(const QString& msg);
};

