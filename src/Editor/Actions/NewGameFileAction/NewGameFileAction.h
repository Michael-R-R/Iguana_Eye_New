#pragma once

#include "BaseAction.h"

class ApplicationWindow;

class NewGameFileAction : public BaseAction
{

public:
    NewGameFileAction(ApplicationWindow* window, InputKey& shortcut, QObject* parent = nullptr);
    ~NewGameFileAction() {}
};

