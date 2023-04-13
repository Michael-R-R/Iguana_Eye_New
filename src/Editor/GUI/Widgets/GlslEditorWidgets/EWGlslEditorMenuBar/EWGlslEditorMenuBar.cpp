#include "EWGlslEditorMenuBar.h"

EWGlslEditorMenuBar::EWGlslEditorMenuBar(QWidget* parent) :
    QMenuBar(parent),
    fileMenu(new EWGlslEditorFileMenu(this)),
    editMenu(new EWGlslEditorEditMenu(this)),
    viewMenu(new EWGlslEditorViewMenu(this))
{
    this->addMenu(fileMenu);
    this->addMenu(editMenu);
    this->addMenu(viewMenu);
}

void EWGlslEditorMenuBar::startup(EWGlslEditor* glEditor)
{
    setupFileMenu(glEditor);
    setupEditMenu(glEditor);
    setupViewMenu(glEditor);
}

void EWGlslEditorMenuBar::setupFileMenu(EWGlslEditor* glEditor)
{
    fileMenu->startup(glEditor);
}

void EWGlslEditorMenuBar::setupEditMenu(EWGlslEditor* glEditor)
{
    editMenu->startup(glEditor);
}

void EWGlslEditorMenuBar::setupViewMenu(EWGlslEditor* glEditor)
{
    viewMenu->startup(glEditor);
}
