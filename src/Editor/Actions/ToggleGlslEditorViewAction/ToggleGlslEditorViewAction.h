#pragma once

#include "MenuAction.h"

class EWGlslEditor;

class ToggleGlslEditorViewAction : public MenuAction
{

public:
    ToggleGlslEditorViewAction(EWGlslEditor* editor, InputKey& shortcut, QObject* parent = nullptr);
    ~ToggleGlslEditorViewAction() {}
};

