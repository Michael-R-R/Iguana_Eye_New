#pragma once

#include <QObject>

class IELocalEntityScript : public QObject
{
    Q_OBJECT

    int entityId;

public:
    Q_INVOKABLE IELocalEntityScript(const int val, QObject* parent = nullptr);
    ~IELocalEntityScript() {}

public slots:
    int id() const { return entityId; }
};

