#pragma once

#include "BaseAction.h"

class EWGlslEditor;

class SaveAsShaderAction : public BaseAction
{
public:
    SaveAsShaderAction(EWGlslEditor* editor, InputKey& shortcut, QObject* parent = nullptr);
    ~SaveAsShaderAction() {}
};

