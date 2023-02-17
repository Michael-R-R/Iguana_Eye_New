#include "EGlslEditorWindow.h"
#include "AppStartEvent.h"

EGlslEditorWindow::EGlslEditorWindow(QWidget* parent) :
    EWindow("GLSL Editor", parent),
    glslEditorWidget(new EWGlslEditor(this))
{
    this->setFloating(true);
    this->setWidget(glslEditorWidget);
}

void EGlslEditorWindow::startup(const AppStartEvent& event)
{
    glslEditorWidget->startup(event);
}
