#include "EGlslEditorWindow.h"
#include "AppStartEvent.h"

EGlslEditorWindow::EGlslEditorWindow(QWidget* parent) :
    EWindow("GLSL Editor", parent),
    glslEditorWidget(std::make_unique<EWGlslEditor>(this))
{
    this->resize(450, 250);
    this->setFloating(true);
    this->setWidget(&(*glslEditorWidget));
}

void EGlslEditorWindow::startup(const AppStartEvent& event)
{
    glslEditorWidget->startup(event);

    connect(&glslEditorWidget->getVertSrcEditor(), &EWGlslSrcEditor::modified, this, &EGlslEditorWindow::setModified);
    connect(&glslEditorWidget->getFragSrcEditor(), &EWGlslSrcEditor::modified, this, &EGlslEditorWindow::setModified);
}
