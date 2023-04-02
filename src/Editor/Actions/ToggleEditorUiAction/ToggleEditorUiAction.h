#pragma once

#include <BaseAction.h>

class EGUI;

class ToggleEditorUiAction : public BaseAction
{
    bool status;

public:
    ToggleEditorUiAction(InputKey& shortcut, EGUI* ui, QObject* parent = nullptr);
    ~ToggleEditorUiAction();
};

