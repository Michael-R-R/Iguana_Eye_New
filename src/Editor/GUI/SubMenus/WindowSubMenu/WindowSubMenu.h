#pragma once

#include "SubMenu.h"

class WindowSubMenu : public SubMenu
{

public:
    WindowSubMenu(QWidget* parent = nullptr);
    ~WindowSubMenu() {}

    void setupActions();
};

