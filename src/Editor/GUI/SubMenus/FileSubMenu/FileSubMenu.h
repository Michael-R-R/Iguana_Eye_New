#pragma once

#include "SubMenu.h"

class AppStartEvent;

class FileSubMenu : public SubMenu
{

public:
    FileSubMenu(QWidget* parent = nullptr);
    ~FileSubMenu();

    void setupActions(const AppStartEvent& event);
};

