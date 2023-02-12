#pragma once

#include <MenuAction.h>

class EditorUi;

class ToggleEditorUiAction : public MenuAction
{
    bool status;

public:
    ToggleEditorUiAction(InputKey* shortcut, EditorUi* ui, QObject* parent = nullptr);
    ~ToggleEditorUiAction();
};

