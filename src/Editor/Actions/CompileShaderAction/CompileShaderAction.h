#pragma once

#include "BaseAction.h"

class EWGlslEditor;
class IEShaderManager;

class CompileShaderAction : public BaseAction
{

public:
    CompileShaderAction(EWGlslEditor* editor, IEShaderManager& manager,
                        InputKey& shortcut, QObject* parent = nullptr);
    ~CompileShaderAction() {}
};

