#pragma once

#include <QObject>

class IEInput;

class IEGlobalInputScript : public QObject
{
    Q_OBJECT

    // DOES NOT OWN THIS POINTER
    IEInput* input;

public:
    IEGlobalInputScript(IEInput* val, QObject* parent = nullptr);
    ~IEGlobalInputScript();

public slots:
    bool isPressed(const QString& keyName);
};

