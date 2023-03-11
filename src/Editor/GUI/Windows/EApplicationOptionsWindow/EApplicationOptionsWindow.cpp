#include "EApplicationOptionsWindow.h"
#include "EWSelectApplicationOption.h"
#include "AppStartEvent.h"
#include "Editor.h"
#include "IEGame.h"

EApplicationOptionsWindow::EApplicationOptionsWindow(QWidget* parent) :
    EWindow("Options", parent),
    selectOptionsWidget(new EWSelectApplicationOption(this))
{
    this->setWindowFlags(Qt::WindowStaysOnTopHint);
    this->setFeatures(QDockWidget::DockWidgetClosable | QDockWidget::DockWidgetFloatable);
    this->resize(450, 250);
    this->setFloating(true);
    this->setWidget(selectOptionsWidget);
}

EApplicationOptionsWindow::~EApplicationOptionsWindow()
{

}

void EApplicationOptionsWindow::startup(const AppStartEvent& event)
{
    auto* editorInput = event.getEditor()->getInput();
    auto& editorInputContainer = editorInput->getInputContainer();

    auto& gameInput = event.getGame()->getIEInput();
    auto& gameInputContainer = gameInput.getInputContainer();

    selectOptionsWidget->setupGameGroupBox(gameInputContainer);
    selectOptionsWidget->setupEditorGroupBox(editorInputContainer);
}
