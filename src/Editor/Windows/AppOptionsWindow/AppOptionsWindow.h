#pragma once

#include <QEvent>
#include <QMouseEvent>

#include "Window.h"

class AppStartEvent;
class SelectAppOptionsWidget;

class AppOptionsWindow : public Window
{
    Q_OBJECT

    SelectAppOptionsWidget* selectOptionsWidget;

public:
    AppOptionsWindow(QWidget* parent = nullptr);
    ~AppOptionsWindow();

    void setup(const AppStartEvent& event);
};

