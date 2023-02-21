#pragma once

#include "SubMenu.h"

class AppStartEvent;
class EWGlslEditor;

class EWGlslEditorFileMenu : public SubMenu
{

public:
    EWGlslEditorFileMenu(QWidget* parent = nullptr);
    ~EWGlslEditorFileMenu() {}

    void startup(const AppStartEvent& event, EWGlslEditor* editor);
};

