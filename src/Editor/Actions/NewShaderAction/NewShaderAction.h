#pragma once

#include "MenuAction.h"

class IENameManager;
class IEShaderManager;

class NewShaderAction : public MenuAction
{

public:
    NewShaderAction(IENameManager* nameManager, IEShaderManager* shaderManager,
                    InputKey* shortcut, QObject* parent = nullptr);
    ~NewShaderAction() {}
};

