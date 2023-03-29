#pragma once

#include "EWindow.h"

class EMessageLogWindow : public EWindow
{
    Q_OBJECT

public:
    EMessageLogWindow(QWidget* parent = nullptr);
    ~EMessageLogWindow();

    void startup(const AppStartEvent& event) override;
};

