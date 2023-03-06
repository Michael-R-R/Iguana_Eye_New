#pragma once

#include <QObject>

class IETime;

class IEGlobalTimeScript : public QObject
{
    Q_OBJECT

    // DOES NOT OWN THIS POINTER
    IETime* time;

public:
    IEGlobalTimeScript(IETime* val, QObject* parent = nullptr);
    ~IEGlobalTimeScript();

public slots:
    float fps();
    float deltaTime();
};

