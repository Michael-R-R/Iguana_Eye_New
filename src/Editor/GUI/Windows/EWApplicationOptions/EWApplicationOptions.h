#pragma once

#include <QEvent>
#include <QMouseEvent>

#include "EWWindow.h"

class AppStartEvent;
class EWSelectApplicationOption;

class EWApplicationOptions : public EWWindow
{
    Q_OBJECT

    EWSelectApplicationOption* selectOptionsWidget;

public:
    EWApplicationOptions(QWidget* parent = nullptr);
    ~EWApplicationOptions();

    void setup(const AppStartEvent& event);
};

