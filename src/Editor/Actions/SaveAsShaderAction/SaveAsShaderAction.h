#pragma once

#include "MenuAction.h"

class EWGlslEditor;
class IEShaderManager;

class SaveAsShaderAction : public MenuAction
{
public:
    SaveAsShaderAction(EWGlslEditor* editor, IEShaderManager& shaderManager,
                       InputKey& shortcut, QObject* parent = nullptr);
    ~SaveAsShaderAction() {}
};

