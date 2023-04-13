#pragma once

#include <QStatusBar>

class StatusBar : public QStatusBar
{
    Q_OBJECT

public:
    StatusBar(QWidget* parent = nullptr);
    ~StatusBar();

    void startup();
};

