#pragma once

#include "SubMenu.h"

class EWGlslEditor;

class EWGlslEditorFileMenu : public SubMenu
{

public:
    EWGlslEditorFileMenu(QWidget* parent = nullptr);
    ~EWGlslEditorFileMenu() {}

    void startup(EWGlslEditor* glEditor);
};

