#pragma once

#include <MenuAction.h>

class EditorUi;

class ToggleUiAction : public MenuAction
{
    bool status;

public:
    ToggleUiAction(InputKey* shortcut, EditorUi* ui, QObject* parent = nullptr);
    ~ToggleUiAction();
};

