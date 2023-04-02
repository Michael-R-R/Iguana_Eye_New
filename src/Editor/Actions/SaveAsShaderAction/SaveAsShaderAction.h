#pragma once

#include "BaseAction.h"

class EWGlslEditor;
class IEShaderManager;

class SaveAsShaderAction : public BaseAction
{
public:
    SaveAsShaderAction(EWGlslEditor* editor, IEShaderManager& shaderManager,
                       InputKey& shortcut, QObject* parent = nullptr);
    ~SaveAsShaderAction() {}
};

