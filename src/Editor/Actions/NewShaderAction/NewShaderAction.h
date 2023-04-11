#pragma once

#include "BaseAction.h"

class EWGlslEditor;

class NewShaderAction : public BaseAction
{

public:
    NewShaderAction(EWGlslEditor* editor, InputKey& shortcut, QObject* parent = nullptr);
    ~NewShaderAction() {}
};

