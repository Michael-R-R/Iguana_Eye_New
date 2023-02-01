#pragma once

#include "SubMenu.h"

class AppStartEvent;

class GameSubMenu : public SubMenu
{

public:
    GameSubMenu(QWidget* parent = nullptr);
    ~GameSubMenu();

    void setupActions(const AppStartEvent& event);
};

