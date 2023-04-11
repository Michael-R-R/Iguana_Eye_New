#pragma once

#include "BaseAction.h"

class EWGlslEditor;

class CompileShaderAction : public BaseAction
{

public:
    CompileShaderAction(EWGlslEditor* editor, InputKey& shortcut, QObject* parent = nullptr);
    ~CompileShaderAction() {}
};

