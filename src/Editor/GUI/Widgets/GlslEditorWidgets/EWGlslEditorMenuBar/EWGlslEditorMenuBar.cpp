#include "EWGlslEditorMenuBar.h"
#include "AppStartEvent.h"

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

void EWGlslEditorMenuBar::startup(const AppStartEvent& event, EWGlslEditor* editor)
{
    setupFileMenu(event);
    setupEditMenu(event, editor);
    setupViewMenu(event, editor);
}

void EWGlslEditorMenuBar::setupFileMenu(const AppStartEvent& event)
{
    fileMenu->startup(event);
}

void EWGlslEditorMenuBar::setupEditMenu(const AppStartEvent& event, EWGlslEditor* editor)
{
    editMenu->startup(event, editor);
}

void EWGlslEditorMenuBar::setupViewMenu(const AppStartEvent& event, EWGlslEditor* editor)
{
    viewMenu->startup(event, editor);
}
