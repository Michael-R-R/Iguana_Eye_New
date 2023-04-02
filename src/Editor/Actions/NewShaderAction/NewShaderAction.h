#pragma once

#include "BaseAction.h"

class EWGlslEditor;
class IEShaderManager;

class NewShaderAction : public BaseAction
{

public:
    NewShaderAction(EWGlslEditor* editor, IEShaderManager& shaderManager,
                    InputKey& shortcut, QObject* parent = nullptr);
    ~NewShaderAction() {}
};

