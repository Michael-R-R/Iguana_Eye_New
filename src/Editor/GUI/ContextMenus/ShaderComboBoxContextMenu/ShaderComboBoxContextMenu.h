#pragma once

#include "ContextMenu.h"

class IEShaderManager;

class ShaderComboBoxContextMenu : public ContextMenu
{
    // Does not own this pointer
    IEShaderManager* shaderManager;
    uint64_t selectedId;

public:
    ShaderComboBoxContextMenu(QWidget* parent = nullptr);
    ~ShaderComboBoxContextMenu();

    void startup(IEShaderManager* shaderManager);

    void setSelectedId(const uint64_t val) { selectedId = val; }

private:
    void setupDeleteShaderAction();
};

