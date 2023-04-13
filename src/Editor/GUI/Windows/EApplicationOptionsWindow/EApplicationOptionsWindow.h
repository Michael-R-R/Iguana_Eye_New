#pragma once

#include <QEvent>
#include <QMouseEvent>

#include "EWindow.h"

class EWSelectApplicationOption;

class EApplicationOptionsWindow : public EWindow
{
    Q_OBJECT

    EWSelectApplicationOption* selectOptionsWidget;

public:
    EApplicationOptionsWindow(QWidget* parent = nullptr);
    ~EApplicationOptionsWindow();

    void startup() override;
};

