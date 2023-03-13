#pragma once

#include "EWindow.h"

class AppStartEvent;
class EWSelectApplicationOption;

class EApplicationOptionsWindow : public EWindow
{
    Q_OBJECT

    std::unique_ptr<EWSelectApplicationOption> selectOptionsWidget;

public:
    EApplicationOptionsWindow(QWidget* parent = nullptr);
    ~EApplicationOptionsWindow();

    void startup(const AppStartEvent& event);
};

