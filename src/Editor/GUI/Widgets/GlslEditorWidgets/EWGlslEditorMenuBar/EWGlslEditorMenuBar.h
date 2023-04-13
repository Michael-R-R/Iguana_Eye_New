#pragma once

#include <QMenuBar>

#include "EWGlslEditorFileMenu.h"
#include "EWGlslEditorEditMenu.h"
#include "EWGlslEditorViewMenu.h"

class EWGlslEditor;

class EWGlslEditorMenuBar : public QMenuBar
{
    EWGlslEditorFileMenu* fileMenu;
    EWGlslEditorEditMenu* editMenu;
    EWGlslEditorViewMenu* viewMenu;

public:
    EWGlslEditorMenuBar(QWidget* parent = nullptr);
    ~EWGlslEditorMenuBar() {}

    void startup(EWGlslEditor* editor);

private:
    void setupFileMenu(EWGlslEditor* editor);
    void setupEditMenu(EWGlslEditor* editor);
    void setupViewMenu(EWGlslEditor* editor);
};

