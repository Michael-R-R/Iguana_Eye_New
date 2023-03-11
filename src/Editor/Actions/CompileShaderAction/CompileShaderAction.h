#pragma once

#include "MenuAction.h"

class EWGlslEditor;
class IEShaderManager;

class CompileShaderAction : public MenuAction
{

public:
    CompileShaderAction(EWGlslEditor* editor, IEShaderManager& manager,
                        InputKey& shortcut, QObject* parent = nullptr);
    ~CompileShaderAction() {}
};

