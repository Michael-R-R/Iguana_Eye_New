#pragma once

#include "ContextMenu.h"

class IEShaderManager;

class ShaderComboBoxContextMenu : public ContextMenu
{
    // Does not own this pointer
    IEShaderManager* shaderManager;
    unsigned long long selectedId;

public:
    ShaderComboBoxContextMenu(QWidget* parent = nullptr);
    ~ShaderComboBoxContextMenu();

    void startup(IEShaderManager* shaderManager);

    void setSelectedId(const unsigned long long val) { selectedId = val; }

private:
    void setupDeleteShaderAction();
};

