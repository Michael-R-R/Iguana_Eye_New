#pragma once

#include <QObject>

class AppStartEvent;

class EActionManager : public QObject
{

public:
    EActionManager(QObject* parent = nullptr);
    ~EActionManager();

    void setup(const AppStartEvent& event);
};

