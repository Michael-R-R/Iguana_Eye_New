#pragma once

#include "MenuAction.h"

class IEShaderManager;

class NewShaderAction : public MenuAction
{

public:
    NewShaderAction(IEShaderManager* shaderManager,
                    InputKey* shortcut, QObject* parent = nullptr);
    ~NewShaderAction() {}
};

