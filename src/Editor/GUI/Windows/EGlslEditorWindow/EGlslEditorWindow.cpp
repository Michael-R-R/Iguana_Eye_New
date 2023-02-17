#include "EGlslEditorWindow.h"
#include "AppStartEvent.h"

EGlslEditorWindow::EGlslEditorWindow(QWidget* parent) :
    EWindow("GLSL Editor", parent),
    glslEditorWidget(new EWGlslEditor(this))
{
    this->setWidget(glslEditorWidget);
    this->setFloating(true);
}

void EGlslEditorWindow::startup(const AppStartEvent&)
{

}
