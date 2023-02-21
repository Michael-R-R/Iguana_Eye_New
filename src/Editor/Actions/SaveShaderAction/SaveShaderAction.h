#pragma once

#include "MenuAction.h"

class EWGlslEditor;
class IEShaderManager;

class SaveShaderAction : public MenuAction
{
public:
    SaveShaderAction(EWGlslEditor* editor, IEShaderManager* shaderManager,
                     InputKey* shortcut, QObject* parent = nullptr);
    ~SaveShaderAction() {}
};

