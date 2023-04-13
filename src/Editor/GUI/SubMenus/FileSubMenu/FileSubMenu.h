#pragma once

#include "SubMenu.h"

class FileSubMenu : public SubMenu
{

public:
    FileSubMenu(QWidget* parent = nullptr);
    ~FileSubMenu();

    void startup();

private:
    void setupConnections();
};

