#pragma once

#include <QMenuBar>

#include "EWGlslEditorFileMenu.h"
#include "EWGlslEditorEditMenu.h"
#include "EWGlslEditorViewMenu.h"

class AppStartEvent;
class EWGlslEditor;

class EWGlslEditorMenuBar : public QMenuBar
{
    EWGlslEditorFileMenu* fileMenu;
    EWGlslEditorEditMenu* editMenu;
    EWGlslEditorViewMenu* viewMenu;

public:
    EWGlslEditorMenuBar(QWidget* parent = nullptr);
    ~EWGlslEditorMenuBar() {}

    void startup(const AppStartEvent& event, EWGlslEditor* editor);

private:
    void setupFileMenu(const AppStartEvent& event, EWGlslEditor* editor);
    void setupEditMenu(const AppStartEvent& event, EWGlslEditor* editor);
    void setupViewMenu(const AppStartEvent& event, EWGlslEditor* editor);
};

