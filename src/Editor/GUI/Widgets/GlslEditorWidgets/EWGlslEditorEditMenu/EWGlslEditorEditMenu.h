#pragma once

#include "SubMenu.h"

class EWGlslEditor;

class EWGlslEditorEditMenu : public SubMenu
{

public:
    EWGlslEditorEditMenu(QWidget* parent = nullptr);
    ~EWGlslEditorEditMenu() {}

    void startup(EWGlslEditor* editor);
};

