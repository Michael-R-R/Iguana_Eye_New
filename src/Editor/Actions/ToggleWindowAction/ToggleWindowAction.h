#pragma once

#include <MenuAction.h>

class EWindow;

class ToggleWindowAction : public MenuAction
{

public:
    ToggleWindowAction(const QString& title,
                       InputKey* shortcut,
                       EWindow* window,
                       QObject *parent = nullptr);
    ~ToggleWindowAction();
};

