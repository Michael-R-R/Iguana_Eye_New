#pragma once

#include "MenuAction.h"

class ApplicationWindow;

class NewGameFileAction : public MenuAction
{

public:
    NewGameFileAction(ApplicationWindow* window, InputKey& shortcut, QObject* parent = nullptr);
    ~NewGameFileAction() {}
};

