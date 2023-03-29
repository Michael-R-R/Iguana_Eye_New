#pragma once

#include "EWindow.h"
#include "EWMessageLog.h"

class EMessageLogWindow : public EWindow
{
    Q_OBJECT

    EWMessageLog* messageLog;

public:
    EMessageLogWindow(QWidget* parent = nullptr);
    ~EMessageLogWindow();

    void startup(const AppStartEvent& event) override;
};

