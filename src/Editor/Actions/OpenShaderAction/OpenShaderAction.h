#pragma once

#include "BaseAction.h"

class IEShaderManager;

class OpenShaderAction : public BaseAction
{

public:
    OpenShaderAction(IEShaderManager& shaderManager,
                     InputKey& shortcut, QObject* parent = nullptr);
    ~OpenShaderAction() {}
};

