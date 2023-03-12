#pragma once

#include <MenuAction.h>

class EGUI;

class ToggleEditorUiAction : public MenuAction
{
    bool status;

public:
    ToggleEditorUiAction(InputKey& shortcut, EGUI& ui, QObject* parent = nullptr);
    ~ToggleEditorUiAction();
};

