#pragma once

#include "MenuAction.h"

class IEShaderManager;

class OpenShaderAction : public MenuAction
{

public:
    OpenShaderAction(IEShaderManager* shaderManager,
                     InputKey* shortcut, QObject* parent = nullptr);
    ~OpenShaderAction() {}
};

