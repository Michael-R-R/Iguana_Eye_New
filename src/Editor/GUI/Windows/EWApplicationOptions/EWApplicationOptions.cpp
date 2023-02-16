#include "EWApplicationOptions.h"
#include "EWSelectApplicationOption.h"
#include "AppStartEvent.h"
#include "Editor.h"
#include "IEGame.h"

EWApplicationOptions::EWApplicationOptions(QWidget* parent) :
    EWWindow("Options", parent),
    selectOptionsWidget(new EWSelectApplicationOption(this))
{
    this->setWindowFlags(Qt::WindowStaysOnTopHint);
    this->setFeatures(QDockWidget::DockWidgetClosable | QDockWidget::DockWidgetFloatable);
    this->resize(450, 250);
    this->setFloating(true);
    this->setWidget(selectOptionsWidget);
}

EWApplicationOptions::~EWApplicationOptions()
{

}

void EWApplicationOptions::setup(const AppStartEvent& event)
{
    auto editorInput = event.getEditor()->getInput();
    auto editorInputContainer = editorInput->getInputContainer();

    auto gameInput = event.getGame()->getIEInput();
    auto gameInputContainer = gameInput->getInputContainer();

    selectOptionsWidget->setupGameGroupBox(gameInputContainer);
    selectOptionsWidget->setupEditorGroupBox(editorInputContainer);
}
