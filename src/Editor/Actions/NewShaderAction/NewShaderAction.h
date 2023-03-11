#pragma once

#include "MenuAction.h"

class EWGlslEditor;
class IEShaderManager;

class NewShaderAction : public MenuAction
{

public:
    NewShaderAction(EWGlslEditor* editor, IEShaderManager& shaderManager,
                    InputKey& shortcut, QObject* parent = nullptr);
    ~NewShaderAction() {}
};

