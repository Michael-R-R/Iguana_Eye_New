#pragma once

#include "BaseAction.h"

class EWGlslEditor;

class ToggleGlslEditorViewAction : public BaseAction
{

public:
    ToggleGlslEditorViewAction(EWGlslEditor* editor, InputKey& shortcut, QObject* parent = nullptr);
    ~ToggleGlslEditorViewAction() {}
};

