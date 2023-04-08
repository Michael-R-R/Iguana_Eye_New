#pragma once

#include "BaseAction.h"

class ApplicationWindow;

class SaveGameFileAction : public BaseAction
{
public:
    SaveGameFileAction(ApplicationWindow* window, InputKey& shortcut, QObject* parent = nullptr);
    ~SaveGameFileAction();
};

