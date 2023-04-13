#pragma once

#include "SubMenu.h"

class EWGlslEditor;

class EWGlslEditorViewMenu : public SubMenu
{

public:
    EWGlslEditorViewMenu(QWidget* parent = nullptr);
    ~EWGlslEditorViewMenu() {}

    void startup(EWGlslEditor* editor);
};

