#pragma once

#include <MenuAction.h>

class EditorWindowManager;

class AppOptionsAction : public MenuAction
{

public:
    AppOptionsAction(InputKey* shortcut,
                     EditorWindowManager* windowManager,
                     QObject *parent = nullptr);
    ~AppOptionsAction();
};

