#pragma once

#include <MenuAction.h>

class EWindowManager;

class AppOptionsAction : public MenuAction
{

public:
    AppOptionsAction(InputKey* shortcut,
                     EWindowManager* windowManager,
                     QObject *parent = nullptr);
    ~AppOptionsAction();
};

