#pragma once

#include "SubMenu.h"

class GameSubMenu : public SubMenu
{

public:
    GameSubMenu(QWidget* parent = nullptr);
    ~GameSubMenu();

    void setupActions();
};

