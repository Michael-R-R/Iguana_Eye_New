#include "EWGlslEditorMenuBar.h"

EWGlslEditorMenuBar::EWGlslEditorMenuBar(QWidget* parent) :
    QMenuBar(parent),
    fileMenu(new EWGlslEditorFileMenu(this)),
    viewMenu(new EWGlslEditorViewMenu(this))
{
    this->addMenu(fileMenu);
    this->addMenu(viewMenu);
}

void EWGlslEditorMenuBar::startup(EWGlslEditor* glEditor)
{
    setupFileMenu(glEditor);
    setupViewMenu(glEditor);
}

void EWGlslEditorMenuBar::setupFileMenu(EWGlslEditor* glEditor)
{
    fileMenu->startup(glEditor);
}

void EWGlslEditorMenuBar::setupViewMenu(EWGlslEditor* glEditor)
{
    viewMenu->startup(glEditor);
}
