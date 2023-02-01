#pragma once

#include <QStatusBar>

class AppStartEvent;

class StatusBar : public QStatusBar
{
    Q_OBJECT

public:
    StatusBar(QWidget* parent = nullptr);
    ~StatusBar();

    void setupIEObjectConnections(const AppStartEvent& event);
};

