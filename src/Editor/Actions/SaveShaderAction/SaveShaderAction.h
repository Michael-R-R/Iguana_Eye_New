#pragma once

#include "MenuAction.h"

class EWGlslEditor;
class IEShaderManager;

class SaveShaderAction : public MenuAction
{
    bool isShaderActive;

public:
    SaveShaderAction(EWGlslEditor* editor, IEShaderManager& shaderManager,
                     InputKey& shortcut, QObject* parent = nullptr);
    ~SaveShaderAction() {}
};

