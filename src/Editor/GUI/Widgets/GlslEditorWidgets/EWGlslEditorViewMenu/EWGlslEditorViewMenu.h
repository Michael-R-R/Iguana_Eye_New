#pragma once

#include "SubMenu.h"

class AppStartEvent;
class EWGlslEditor;

class EWGlslEditorViewMenu : public SubMenu
{

public:
    EWGlslEditorViewMenu(QWidget* parent = nullptr);
    ~EWGlslEditorViewMenu() {}

    void startup(const AppStartEvent& event, EWGlslEditor* editor);
};

