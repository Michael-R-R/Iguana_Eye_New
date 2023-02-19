#pragma once

#include "SubMenu.h"

class AppStartEvent;
class EWGlslEditor;

class EWGlslEditorEditMenu : public SubMenu
{

public:
    EWGlslEditorEditMenu(QWidget* parent = nullptr);
    ~EWGlslEditorEditMenu() {}

    void startup(const AppStartEvent& event, EWGlslEditor* editor);
};

