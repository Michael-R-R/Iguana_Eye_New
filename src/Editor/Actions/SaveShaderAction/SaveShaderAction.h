#pragma once

#include "BaseAction.h"

class EWGlslEditor;
class IEShaderManager;

class SaveShaderAction : public BaseAction
{
    bool isShaderActive;

public:
    SaveShaderAction(EWGlslEditor* editor, IEShaderManager& shaderManager,
                     InputKey& shortcut, QObject* parent = nullptr);
    ~SaveShaderAction() {}
};

