#pragma once

#include "SubMenu.h"

class AppStartEvent;

class WindowSubMenu : public SubMenu
{

public:
    WindowSubMenu(QWidget* parent = nullptr);
    ~WindowSubMenu() {}

    void setupActions(const AppStartEvent& event);
};

