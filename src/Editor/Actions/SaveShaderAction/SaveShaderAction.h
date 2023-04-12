#pragma once

#include "BaseAction.h"

class EWGlslEditor;

class SaveShaderAction : public BaseAction
{

public:
    SaveShaderAction(EWGlslEditor* editor, InputKey& shortcut, QObject* parent = nullptr);
    ~SaveShaderAction() {}
};

