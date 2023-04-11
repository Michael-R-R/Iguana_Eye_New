#pragma once

#include "BaseAction.h"

class EWGlslEditor;

class OpenShaderAction : public BaseAction
{

public:
    OpenShaderAction(EWGlslEditor* editor, InputKey& shortcut, QObject* parent = nullptr);
    ~OpenShaderAction() {}
};

