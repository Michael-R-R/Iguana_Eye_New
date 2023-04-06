#include "EApplicationOptionsWindow.h"
#include "EWSelectApplicationOption.h"
#include "AppStartEvent.h"
#include "Editor.h"
#include "IEGame.h"
#include "BaseInput.h"
#include "IEInput.h"
#include "EInput.h"

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
    BaseInput* gameInput = &event.getGame()->getIEInput();
    BaseInput* editorInput = event.getEditor()->getInput();

    selectOptionsWidget->setupGameGroupBox(gameInput);
    selectOptionsWidget->setupEditorGroupBox(editorInput);
}
