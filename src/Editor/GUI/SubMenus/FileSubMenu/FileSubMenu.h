#pragma once

#include "SubMenu.h"

class AppStartEvent;

class FileSubMenu : public SubMenu
{

public:
    FileSubMenu(QWidget* parent = nullptr);
    ~FileSubMenu();

    void startup(const AppStartEvent& event);

private:
    void setupConnections(const AppStartEvent& event);
};

