#pragma once

#include <QObject>

class GameStartEvent;
class IETime;

class IEGlobalTimeScript : public QObject
{
    Q_OBJECT

    IETime* time;

public:
    IEGlobalTimeScript(const GameStartEvent& event, QObject* parent = nullptr);
    ~IEGlobalTimeScript();

public slots:
    float fps();
    float deltaTime();
};

